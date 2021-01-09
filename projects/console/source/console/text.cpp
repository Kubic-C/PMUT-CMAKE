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

#include "headers/text.h"

namespace console
{
    render_context::render_context()
        : font_vbo(GL_ARRAY_BUFFER)
    {
        // although the amount of space I am allocating on the VRAM seems absurd,
        // it in total is ~2.88 megabytes, and all modern GPUs can handle that


        // 6 triangles, vec2 position, vec2 tex_coords, vec3 rgb
        size_t size_of_vbo = (sizeof(float)*6*2*2*3)*CHARACTER_RENDER_LIMIT;
        font_vbo.buffer_data(size_of_vbo, nullptr, GL_DYNAMIC_DRAW);
        font_vbo.bind();
        int stride = sizeof(float)*(2+2+3);
        std::cout << stride << '\n';
        font_vao.vertex_attrib_pointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0); // a_pos
        font_vao.vertex_attrib_pointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)8); // a_tex_coords
        font_vao.vertex_attrib_pointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)16); // a_color
        font_vbo.unbind();

        /*
            {   // vec2       // vec2                               // vec3
                x2    , -y2    , ch.xtex_coords[0], ch.ytex_coords[0], color.r, color.g, color.b,
                x2 + w, -y2    , ch.xtex_coords[1], ch.ytex_coords[1], color.r, color.g, color.b,
                x2    , -y2 - h, ch.xtex_coords[2], ch.ytex_coords[2], color.r, color.g, color.b,

                x2 + w, -y2    , ch.xtex_coords[3], ch.ytex_coords[3], color.r, color.g, color.b,
                x2    , -y2 - h, ch.xtex_coords[4], ch.ytex_coords[4], color.r, color.g, color.b,
                x2 + w, -y2 - h, ch.xtex_coords[5], ch.ytex_coords[5], color.r, color.g, color.b,
            };
        */
    }

    void render_context::use_program(abstractgl::program new_font_program)
    {
        font_program = new_font_program;
    }

    void render_context::use_font(abstractgl::ft::font&& new_text_font)
    {
        text_font = new_text_font;
    }

    std::vector<float> render_context::parse_output(glm::vec2 pos, glm::vec3 color, float scale, std::string text)
    {
        std::vector<float> quads;
        for(auto c : text)
        {
            abstractgl::ft::character& ch = text_font.char_set[c];

            float x2 = pos.x + ch.bearing.x * scale;
            float y2 = pos.y - (ch.size.y - ch.bearing.y) * scale;
            float w = ch.size.x * scale;
            float h = ch.size.y * scale;    

            float x_width = x2 + w, y_height = y2 + h;
            std::vector<float> tquad = 
            {   // vec2       // vec2                               // vec3
                x_width, y_height, ch.tex_coords[0], ch.tex_coords[1], color.r, color.g, color.b,
                x2     , y_height, ch.tex_coords[2], ch.tex_coords[3], color.r, color.g, color.b,
                x_width, y2     , ch.tex_coords[4], ch.tex_coords[5], color.r, color.g, color.b,

                x2     , y2     , ch.tex_coords[6], ch.tex_coords[7], color.r, color.g, color.b,
                x_width, y2     , ch.tex_coords[8], ch.tex_coords[9], color.r, color.g, color.b,
                x2     , y_height, ch.tex_coords[10], ch.tex_coords[11], color.r, color.g, color.b,
            };

            quads.reserve(tquad.size());
            quads.insert(quads.end(), tquad.begin(), tquad.end());

            pos.x += ch.advance * scale;
        }

        return quads;
    }

    void render_context::print(glm::vec2 pos, glm::vec3 color, float scale, std::string text)
    {
        font_vao.bind();
        font_program.use();
        text_font.font_atlas.activate(GL_TEXTURE0);

        std::vector<float> quads = parse_output(pos, color, scale, text);
        font_vbo.update_buffer(sizeof(float)*quads.size(), &quads[0]);
        glDrawArrays(GL_TRIANGLES, 0, text.size()*6);

        abstractgl::unbind_texture();
        font_vao.unbind();
    }
}
