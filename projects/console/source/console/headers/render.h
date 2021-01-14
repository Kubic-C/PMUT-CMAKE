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

/*
   render.h deals with rendering directly with opengl, it is a low-level to high-level file
*/

#ifndef CONSOLE_RENDER_H
#define CONSOLE_RENDER_H

#include "base.h"

// the limit for how many characters are going to be on the screen
// note: increasing or decreasing this number will increase or decrease VRAM usage
#define CHARACTER_RENDER_LIMIT 10000

namespace console
{
    // used later in manager.h
    enum class modifier
    {
        non_static_mod, // NON STATIC MOD IS NOT THREAD SAFE
        static_mod,
        perma_mod,
    };

    // holds meta-data of a string. modifiers, and render piority
    struct meta_str
    {
        modifier str_modifier = modifier::non_static_mod; // string modifier
        std::string str = "";          // string
        glm::vec3 rgb;                // rgb
        int rp = 0;                  // render piority
    };

    /* render_context
    * render context allows 
    * and simplies rendering
    * text. along with other
    * misc. renderings
    * 
    * it uses batch rendering
    * to make rendering faster
    * but with the downside of high
    * VRAM usage, 
    * 
    * 
    */
    class render_context
    {
    public:
        render_context();
        ~render_context();

    public: // methods
        // use this to asign a shader program
        void use_program(abstractgl::program font_program);

        // use this to, note: the font already has to have a computed char set. use std::move to prevent creating copies
        void use_font(abstractgl::ft::font& font);

        // free print allows you to print anywhere on the screen, when printing always call full_bind() before doing so
        // note: overusing this function can result in a higher frametime which is slower
        void free_print(std::string text, glm::vec2 pos, glm::vec3 color, float scale);

        // print will print text onto the screen but only on the top left hand side
        // note: this is alot faster to use and is recommended for faster frametime
        // note: this will not print any text inside of the function, it will instead be printed when print_poll() is called
        void print(std::string text, glm::vec3 color, float scale);

        /// draws everything in the output_buffer, then clearing it. when printing always call full_bind() before
        void print_poll();

        // this will parse the vector, transforming it into something opengl can understand
        void parse_output(std::vector<float>& vector, glm::vec2 pos, glm::vec3 color, float scale, std::string text);

        // this will parse a meta_str vector
        void parse_meta_str_vector(const std::vector<meta_str>& vector);

        // bind everything needed to print,
        void full_bind();

        // unbind everyting
        void full_unbind();

        // set start pos
        void set_start(int x, int y);

        // set projection uniform in vertex shader
        void set_projection(glm::fmat4 projection);

    public: // global vars
        abstractgl::ft::font* text_font; // this is the font that will be used to render
        int wrapping_x = 0; // wraps to the nextline if x > wrapping_x

    private:
        abstractgl::program font_program; // this is shader program that will be responsible for rendering text
        abstractgl::vertex_array font_vao; // contains how data should be read
        abstractgl::vertex_buffer font_vbo; // contains raw data
        abstractgl::vertex_buffer font_indi; // inidces
        std::vector<float>* output_buffer; // used for print
        int n_of_char = 0; // the amount of characters to be rendered
        float print_x = 0; // tell where text inside of print poll should get printed
        float print_y = 0; // tell where text inside of print poll should get printed
        glm::ivec2 start; // begginning of where print_poll will print

        // generate all indices up to the CHARACTER_LIMIT
        void generate_indexes();

        // next line
        void nextline(float& start_x, float& x2, float& y2);
    };
}
 
#endif // CONSOLE_RENDER_H