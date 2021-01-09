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

#ifndef CONSOLE_BITMAP_H
#define CONSOLE_BITMAP_H

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

        // this will not acutally print anything, this will instead add to an output buffer
        void print(glm::vec2 pos, glm::vec3 color, float scale, std::string text);

        // this will parse the output buffer. whist also updating memory in VRAM
        std::vector<float> parse_output(glm::vec2 pos, glm::vec3 color, float scale, std::string text);
    private:
        abstractgl::program font_program; // this is shader program that will be responsible for rendering text
        abstractgl::ft::font text_font; // this is the font that will be used to render
        abstractgl::vertex_array font_vao; // contains how data should be read
        abstractgl::vertex_buffer font_vbo; // contains raw data
    };
}
 
#endif // CONSOLE_BITMAP_H