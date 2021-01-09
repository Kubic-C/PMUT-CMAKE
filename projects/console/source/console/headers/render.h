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

/*
    text.h deals with rendering text(hence the name)
*/

#ifndef CONSOLE_RENDER_H
#define CONSOLE_RENDER_H

#include "base.h"

// I chose 10000 becuase, lets be real here 10000 characters is never going to 
// be on the screen at once, and all modern GPU(2010 and after, in terms of VRAM) are going to
// be able handle it.
#define CHARACTER_RENDER_LIMIT 10000

namespace console
{
    int abstract_ft_test();

    /* render_context
    * render context allows 
    * and simplies rendering
    * text. along with other
    * misc. renderings
    * 
    * it uses batch rendering
    * to make rendering faster
    * but with the downside of high
    * VRAM usage, which is only 
    * a couple of megabytes but
    * a decent amout none the less.
    * 
    * increasing the CHARACTER_RENDER_LIMIT
    * will also increase the amout of
    * VRAM usage.
    * 
    */
    class render_context
    {
    public:
        render_context();

    public: // methods
        // use this to asign a shader program
        void use_program(abstractgl::program font_program);

        // use this to, note: the font already has to have a computed char set. use std::move to prevent creating copies
        void use_font(abstractgl::ft::font&& font);

        // free print allows you to print anywhere on the screen, when printing always call full_bind() before doing so
        // note: overusing this function can result in a higher frametime which is slower
        void free_print(std::string text, glm::vec2 pos, glm::vec3 color, float scale);

        // print will print text onto the screen but only on the top left hand side
        // note: this is alot faster to use and is recommended for faster frametime
        // note: this will not print any text inside of the function, it will instead be printed when print_poll() is called
        void print(std::string text, glm::vec3 color, float scale);

        /// draws everything in the output_buffer, then clearing it. when printing always call full_bind() before
        void print_poll();

        // this will parse the output buffer. whist also updating memory in VRAM
        void parse_output(std::vector<float>& vector, glm::vec2 pos, glm::vec3 color, float scale, std::string text);

        // bind everything needed to print,
        void full_bind();

        // unbind everyting
        void full_unbind();

        // set start pos
        void set_start(int x, int y);

        // set projection uniform in vertex shader
        void set_projection(glm::fmat4 projection);

    private:
        abstractgl::program font_program; // this is shader program that will be responsible for rendering text
        abstractgl::ft::font text_font; // this is the font that will be used to render
        abstractgl::vertex_array font_vao; // contains how data should be read
        abstractgl::vertex_buffer font_vbo; // contains raw data
        abstractgl::vertex_buffer font_indi; // inidces
        std::vector<float> output_buffer; // used for print
        int n_of_char = 0; // the amount of characters to be rendered
        int print_x = 0; // tell where text inside of print poll should get printed
        int print_y = 0; // tell where text inside of print poll should get printed
        glm::ivec2 start; // begginning of where print_poll will print

        // generate all indices up to the CHARACTER_LIMIT
        void generate_indexes();
    };
}
 
#endif // CONSOLE_RENDER_H