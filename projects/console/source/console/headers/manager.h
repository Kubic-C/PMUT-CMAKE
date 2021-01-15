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

/* manager.h
 * manager.h as the name implies
 * manages the console.
 * 
 * all input/output should go through
 * through the manager class.
 * 
*/

#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include "render.h"

#include <mutex>

#define OGL_VERSION 4, 3
#define STR_OGL_VERSION "4.3"

namespace console
{
    // returns true if _1 > _2
    bool highest_rp(const meta_str& _1, const meta_str& _2);

    // returns true if static
    bool remove_if_non_static(meta_str meta_str);

    // returns true if NOT perma
    bool remove_if_not_perma(meta_str meta_str);

    /* manager class
     * 
     * the manager class when initliazed
     * WILL start opengl and create a window
     * with the paremeters given to the contructor
     * 
     * thread-safe impl
     * 
     * the manager class handles strings in a specific
     * way. there are types of string modifiers that will modify
     * their position on screen, and how long they stay 
     * the screen.
     * 
     * NOTE: these string modifiers cannot be added to strings that are printed through free_print
     * listed below are the types of strings:
     * 
     *  - non-static strings - these strings will be removed from the screen unless printed again
     * 
     *  - static strings - these strings only have to be added to the output buffer once
     *  to stay on the screen, but can be removed by the user or by the manager
     * 
     *  - perma strings - these strings are added once and can never be removed.
     * 
     *  - render piority - strings with high render piority will get rendered first and vice versa,
     *  NOTE: this(^^^) is compatible with any string modifier
     * 
    */
    class manager
    {
    public:
        manager(std::string name, int width, int height, bool& good);
        ~manager();

    public: // input - methods
        void copy_last_input_to_active_buffer();        

        std::string get_input();

    public: // output - methods
        // call render.poll(), and sorts meta_str
        void poll();

        // add to string buffer
        void print(std::string text, modifier modifier_, int rp, 
                float r, float g, float b);

        // print freely wherever on the string
        void free_print(std::string text, 
                float r, float g, float b, float x, float y, float scale);

        // print multiple
        template<typename ... text_p>
        void print_m(modifier modifier_, int rp, float r, float g, float b, const text_p& ... text_a)
        {
            std::string text = "";
            ((text += convert_to_string(text_a)), ...);
            print(text, modifier_, rp, r, g, b);
        }

        // remove everything, execept perma strings
        void clear_output_buffer();

    public: // settings - methods
        // set the rendering context
        void use_render_context(render_context& render_context);

        // set the current font, font is fully expected to be computed
        void use_font(abstractgl::ft::font& font);
    
        // error handling; correct the error
        void handle_error();

        // binds the manager, in order to use managers call this
        void bind();

    public: // callbacks - methods
        // set all callbacks, only do this when render_context is set
        void set_all_callbacks();

        // window size callback, sets uniform projection
        static void window_size_callback(GLFWwindow* window, int width, int height);

        // key callback, this will allow keyboard shortcuts to be possible
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // char callback, this will all keyboard input into the active_input var
        static void character_callback(GLFWwindow* window, unsigned int codepoint);

        // frame buffer callback, this is used because not all systems return 
        // the size of the window in pixels, which glViewport needs
        static void framebuffer_callback(GLFWwindow* window, int width, int height);

        // message callback
        static void message_callback(
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam 
        );

        void set_enter_callback(void(*enter_callback_p)(const std::string& string));

    public:
        // output
        GLFWwindow* window;

        // input
        std::string active_input; // active input buffer.
        std::vector<std::string> last_input; // all inputs previous to the active input.
        void(*enter_callback)(const std::string& string);

        // other
        std::mutex mtx; // allows thread safe
        static manager* manager_s; // allows static function to interact with the current manager

    protected: // members
        // output
        render_context* render; // renderer
        std::vector<meta_str> meta_str_buffer; // output meta str buffer
        int width, height; // width and height of the window

        // input
        int last_input_index; // allows the user to cylce to previous indexes

    };
}

#endif // CONSOLE_MANAGER_H