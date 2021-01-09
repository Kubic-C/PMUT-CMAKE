/*
    PMUT (Porter Multi Use Terminal) is a multi use command line,
    that can in the future do networking, file manipulation, and
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

#define OGL_VERSION 4,0

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

    public: // input - methods
        void copy_last_input_to_active_buffer();        

    public: // output - methods
        // call render.poll(), and sorts meta_str
        void poll();

        // add to string buffer
        void print(std::string text, modifier modifier_, int rp, float r, float b, float g);

        // print freely wherever on the string
        void free_print(std::string text, float r, float b, float g, float x, float y);

        // remove everything, execept perma string
        void clear_output_buffer();

    public: // settings - methods
        // set the rendering context, use std::move
        void use_render_context(render_context& render_context);

        // set the current font, font is fully expected to be computed
        void use_font(abstractgl::ft::font& font);
    
    public: // callbacks - methods
        // set all callbacks, only do this when render_context is set
        void set_all_callbacks();

        // window size callback
        static void window_size_callback(GLFWwindow* window, int width, int height);

        // key callback
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        // char callback
        static void character_callback(GLFWwindow* window, unsigned int codepoint);

    public: // members
        // output
        render_context* render; // renderer
        std::vector<meta_str> meta_str_buffer; // output meta str buffer
        GLFWwindow* window; // window  
        int width, height; // width and height of the window

        // input
        std::string active_input; // active input buffer.
        std::vector<std::string> last_input; // all inputs previous to the active input.
        int last_input_index; // allows the user to cylce to previous indexes

    };

    extern manager* current_manager;
}

#endif // CONSOLE_MANAGER_H