/*
    PMUT (Porter Multi Use Terminal) is a multi use command line,
    that can do networking, file manipulation, and
    live app manipulation.
    
    PMUT  Copyright (C) 2021 Sawyer Porter

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "headers/manager.h"
#include <algorithm>

namespace console
{
    bool highest_rp(const meta_str& _1, const meta_str& _2)
    {
        return _1.rp > _2.rp;
    }

    bool remove_if_non_static(meta_str meta_str_p)
    {
        return meta_str_p.str_modifier == modifier::non_static_mod;
    }

    bool remove_if_not_perma(meta_str meta_str_p)
    {
         return meta_str_p.str_modifier != modifier::perma_mod;
    }

    manager::manager(std::string name, int width, int height, bool& good)
        : window(nullptr), width(width), height(height)
    {
        std::string gl_str; 
        window = abstractgl::startup(
            abstractgl::window_data(name, width, height), gl_str, OGL_VERSION);

        good = window;
        if(!good)
        {
            std::cout << gl_str 
                      << "\ninsure that gpu drivers have OpenGL version: " << STR_OGL_VERSION << '\n';
            return;
        }
    }

    // definition of static varible
    manager* manager::manager_s = nullptr;

    manager::~manager()
    {
        glfwTerminate();
    }

    void manager::copy_last_input_to_active_buffer()
    {
        mtx.lock();
        active_input = last_input[last_input_index];
        mtx.unlock();
    }

    std::string manager::get_input()
    {
        std::lock_guard<std::mutex> mtx_(mtx);
        return active_input;
    }

    void manager::poll()
    {
        mtx.lock();
        handle_error();

        // sort the vector into de-ascending order based into render piority
        std::stable_sort(meta_str_buffer.begin(), meta_str_buffer.end(), &highest_rp);

        // this will take everything in the meta_str vector
        render->parse_meta_str_vector(
             meta_str_buffer);

        render->wrapping_x = width;

        // print everything in the buffer
        render->full_bind();
        render->print_poll();
        render->full_unbind();

        meta_str_buffer.erase(std::remove_if(meta_str_buffer.begin(), meta_str_buffer.end(),
                 &remove_if_non_static), meta_str_buffer.end());
        mtx.unlock();
    }

    void manager::print(std::string text, modifier modifier_, int rp, float r, float g, float b)
    {
        mtx.lock();
        meta_str_buffer.push_back((meta_str){modifier_, text, glm::ivec3(r, g, b), rp});
        mtx.unlock();
    }

    void manager::free_print(std::string text, float r, float g, float b, float x, float y, float scale)
    {
        mtx.lock();
        render->full_bind();
        render->free_print(text, glm::vec2(x, y), glm::vec3(r, g, b), scale);
        render->full_unbind();
        mtx.unlock();
    }

    void manager::clear_output_buffer()
    {
        meta_str_buffer.erase(std::remove_if(meta_str_buffer.begin(), meta_str_buffer.end(),
                 &remove_if_not_perma), meta_str_buffer.end());
    }

    void manager::use_render_context(render_context& render_context_p)
    {
        mtx.lock();
        render = &render_context_p;
        // call this to setup projection uniform and render print poll start
        window_size_callback(window, width, height);
        mtx.unlock();
    }

    void manager::use_font(abstractgl::ft::font& font)
    {
        mtx.lock();
        render->use_font(font);
        mtx.unlock();
    }

    void manager::bind()
    {
        mtx.lock();
        manager_s = this;
        mtx.unlock();
    }

    void manager::handle_error()
    {
        // GL_INVALID_ERROR, usally comes from not enough space allocated
        if(glGetError() == GL_INVALID_VALUE)
            clear_output_buffer();
    }

    void manager::set_all_callbacks()
    {
        mtx.lock();
        // credits to https://stackoverflow.com/a/59428098
        glfwSetWindowSizeLimits(window, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE); // make sure not to miss any keys
        glfwSetFramebufferSizeCallback(window, framebuffer_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);
        glfwSetCharCallback(window, character_callback);
        glfwSetKeyCallback(window, key_callback);

        glEnable              ( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( message_callback, 0 );
        mtx.unlock();
    }

    void manager::window_size_callback(GLFWwindow* window, int width, int height)
    {
       //manager_s->mtx.lock();
       manager_s->render->set_start(0, height);
       manager_s->render->set_projection(glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)));
       manager_s->width = width, manager_s->height = height;
       //manager_s->mtx.unlock();
    }

    void manager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        //manager_s->mtx.lock();
        static short int last_key;
        switch(key)
        {
            case GLFW_KEY_F1: // clear static strings
                if(action == GLFW_PRESS)
                    manager_s->clear_output_buffer();
                break;

            case GLFW_KEY_F2:
                if(action == GLFW_PRESS || action == GLFW_REPEAT)
                    manager_s->print("static string mod test\n", console::modifier::static_mod, -1, 0.5f, 0.0f, 1.0f);
                break;

            case GLFW_KEY_V: // get the clipboard
                if(last_key == GLFW_KEY_LEFT_CONTROL && (action == GLFW_PRESS || action == GLFW_REPEAT))
                {
                    // users may try to paste images or some unsupported formate
                    // so this is here to stop seg faults from crashing the app/program
                    // this try-catch block is not full-proof
                    try
                    {
                        std::string buf = glfwGetClipboardString(window);
                        manager_s->active_input += buf;
                    }
                    catch(std::exception& e)
                    {
                        manager_s->print_m(console::modifier::static_mod, -1, 1.0f, 0.0f, 0.0f,
                            "user attempted to paste an invalid string to the active input buffer\n",
                            e.what(), '\n');
                    }
                }
                manager_s->mtx.unlock();
                return;

            case GLFW_KEY_C: // set the clipboard
                if(last_key == GLFW_KEY_LEFT_CONTROL && (action == GLFW_PRESS || action == GLFW_REPEAT))
                    glfwSetClipboardString(window, 
                            manager_s->active_input.c_str());

                manager_s->mtx.unlock();
                return;

            case GLFW_KEY_ENTER: // submit input
                if(manager_s->active_input.find_first_not_of(' ') 
                        == std::string::npos && action != GLFW_PRESS)
                    break;
                manager_s->enter_callback(manager_s->active_input);
                manager_s->last_input.push_back(manager_s->active_input);
                manager_s->active_input.clear();
                manager_s->last_input_index = manager_s->last_input.size()-1;
                break;

            case GLFW_KEY_BACKSPACE: // pop back last character in active_input
                if(!manager_s->active_input.empty() && (action == GLFW_PRESS || action == GLFW_REPEAT))
                    manager_s->active_input.pop_back();
                break;

            default:
                break;
        }
        last_key = key;

        //manager_s->mtx.unlock();
    }

    void manager::character_callback(GLFWwindow* window, unsigned int codepoint)
    {
        //manager_s->mtx.lock();
        manager_s->active_input += (char)codepoint;
        //manager_s->mtx.unlock();
    }

    void manager::framebuffer_callback(GLFWwindow* window, int width, int height)
    {
       // manager_s->mtx.lock();
        glViewport(0, 0, width, height);
       // manager_s->mtx.unlock();
    }

    void manager::message_callback(
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam 
    )
    {
        //manager_s->mtx.lock();
        std::cout << type << '\n' << id << '\n' << severity << '\n' << message << '\n';
        //manager_s->mtx.unlock();
    }

    void manager::set_enter_callback(void(*enter_callback_p)(const std::string& string))
    {
        enter_callback = enter_callback_p;
    }

}