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

#include "headers/startup.h"

namespace abstractgl
{
    window_data::window_data()
    {
    }

    window_data::window_data(std::string name, int width, int height)
        : name(name), width(width), height(height)
    {
    }

    void hint_to_core(int major, int minor)
    {
       glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
       glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
       glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    bool start_glfw()
    {
        return glfwInit() == GLFW_TRUE;
    }

    bool start_glew()
    {
        return glewInit() == GLEW_OK;
    }

    void create_window(GLFWwindow*& window, window_data window_data)
    {
        window = nullptr;
        window = glfwCreateWindow(window_data.width, window_data.height,
              window_data.name.c_str(), nullptr, nullptr);
    }

    GLFWwindow* create_window(window_data window_data)
    {
        GLFWwindow* window;
        create_window(window, window_data);
        return window; 
    }

    void startup(GLFWwindow*& window, window_data window_data, std::string& err, int major, int minor)
    {
        if(!start_glfw())
        {
            err = GLFW_FAILED;
            return;
        }    

        // loading core, this sets the version of OpenGL we want to use.
        hint_to_core(major, minor);

        create_window(window, window_data);
        if(!window) // if(window == nullptr)
        {
            glfwTerminate();
            err = WINDOW_CREATION_FAILED;
            return;
        }

        glfwMakeContextCurrent(window);

        if(!start_glew())
        {
            err = GLEW_FAILED;
            return;
        }
    }

    // starts up glfw, creates a window, and then starts up glew
    GLFWwindow* startup(window_data window_data, std::string& err, int major, int minor)
    {
        GLFWwindow* window = nullptr;
        startup(window, window_data, err, major, minor);
        return window;
    }

    void enable_blend()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}