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

#include "headers/render.h"

namespace console
{
    render_context::render_context()
        : font_vbo(GL_ARRAY_BUFFER), font_indi(GL_ELEMENT_ARRAY_BUFFER), output_buffer(new std::vector<float>)
    {
        // although the amount of space I am allocating on the VRAM seems absurd,
        // it in total is ~2.88 megabytes, and all modern GPUs can handle that


        // 6 triangles, vec2 position, vec2 tex_coords, vec3 rgb
        size_t size_of_vbo = (sizeof(float)*4*2*2*3)*CHARACTER_RENDER_LIMIT;
        font_vbo.buffer_data(size_of_vbo, nullptr, GL_DYNAMIC_DRAW);
        font_vbo.bind();
        int stride = sizeof(float)*(2+2+3);
        font_vao.vertex_attrib_pointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0); // a_pos
        font_vao.vertex_attrib_pointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)8); // a_tex_coords
        font_vao.vertex_attrib_pointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)16); // a_color
        font_vbo.unbind();

        generate_indexes();
    }

    render_context::~render_context()
    {
        font_indi.delete_b();
        font_vbo.delete_b();
        font_vao.delete_a();
        delete output_buffer;
    }

    void render_context::use_program(abstractgl::program new_font_program)
    {
        font_program = new_font_program;
    }

    void render_context::use_font(abstractgl::ft::font& new_text_font)
    { 
        text_font = &new_text_font;
    }

    void render_context::parse_output(std::vector<float>& vector, glm::vec2 pos, glm::vec3 color, float scale, std::string text)
    {
        // save the position of x, so if there is a newline character x = pos.x
        float x = pos.x;
        for(auto c : text)
        {
            switch(c) { case '\n': nextline(pos.x, x, pos.y); continue; }

            abstractgl::ft::character& ch = text_font->char_set[c];

            float x2 = x + ch.bearing.x * scale;
            float y2 = pos.y - ch.bearingy_minus_sizey * scale;
            float w = ch.size.x * scale;
            float h = ch.size.y * scale;    

            float x_width = x2 + w, y_height = y2 + h;
            std::vector<float> tquad = // this will calculate the final vertex for the character
            {   // vec2 - pos       // vec2 - tex coords                // vec3 - color
                x_width, y_height,  ch.tex_coords[0], ch.tex_coords[1], color.r, color.g, color.b,
                x2     , y_height,  ch.tex_coords[2], ch.tex_coords[3], color.r, color.g, color.b,
                x_width, y2      ,  ch.tex_coords[4], ch.tex_coords[5], color.r, color.g, color.b,
                x2     , y2      ,  ch.tex_coords[6], ch.tex_coords[7], color.r, color.g, color.b,
            };

            vector.reserve(tquad.size());
            vector.insert(vector.end(), tquad.begin(), tquad.end());

            x += ch.advance * scale;
        }
    }

    void render_context::parse_meta_str_vector(const std::vector<meta_str>& vector)
    {
        // save the position of x, so if there is a newline character x = pos.x
        float x = print_x, y = print_y;
        for(meta_str mstr : vector)
        {
            for(auto c : mstr.str)
            {
                switch(c) { case '\n': nextline(print_x, x, y); continue; }

                abstractgl::ft::character& ch = text_font->char_set[c];

                float x2 = x + ch.bearing.x;
                float y2 = y - ch.bearingy_minus_sizey;
                float w = ch.size.x;
                float h = ch.size.y;    

                float x_width = x2 + w, y_height = y2 + h;
                std::vector<float> tquad = // this will calculate the final vertex for the character
                {   // vec2 - pos       // vec2 - tex coords                // vec3 - color
                    x_width, y_height,  ch.tex_coords[0], ch.tex_coords[1], mstr.rgb.r, mstr.rgb.g, mstr.rgb.b,
                    x2     , y_height,  ch.tex_coords[2], ch.tex_coords[3], mstr.rgb.r, mstr.rgb.g, mstr.rgb.b,
                    x_width, y2      ,  ch.tex_coords[4], ch.tex_coords[5], mstr.rgb.r, mstr.rgb.g, mstr.rgb.b,
                    x2     , y2      ,  ch.tex_coords[6], ch.tex_coords[7], mstr.rgb.r, mstr.rgb.g, mstr.rgb.b,
                };

                output_buffer->reserve(tquad.size());
                output_buffer->insert(output_buffer->end(), tquad.begin(), tquad.end());
                n_of_char++;

                x += ch.advance;
            }
            switch(mstr.nextline)
            {
                case false:
                    continue;

                case true:
                    nextline(print_x, x, y);
                    break;
            }
        }
    }

    void render_context::free_print(std::string text, glm::vec2 pos, glm::vec3 color, float scale)
    {
        std::vector<float> quads;
        parse_output(quads, pos, color, scale, text);
        font_vbo.update_buffer(sizeof(float)*quads.size(), &quads[0]);
        glDrawElements(GL_TRIANGLES, text.size()*6, GL_UNSIGNED_INT, nullptr);
    }

    void render_context::print(std::string text, glm::vec3 color, float scale)
    {
        std::vector<float> text_quads;
        parse_output(text_quads, glm::ivec2(print_x, print_y), color, scale, text);
        output_buffer->reserve(text_quads.size());
        output_buffer->insert(output_buffer->end(), text_quads.begin(), text_quads.end());
        print_y -= text_font->highest_glpyh_size;
        n_of_char += text.size();
    }

    void render_context::print_poll()
    {
        font_vbo.update_buffer(sizeof(float)*output_buffer->size(), &(*output_buffer)[0]);
        glDrawElements(GL_TRIANGLES, n_of_char*6, GL_UNSIGNED_INT, nullptr);
        output_buffer->clear();
        print_x = start.x; print_y = start.y; 
        n_of_char = 0;
    }

    void render_context::full_bind()
    {
        font_vao.bind();
        font_program.use();
        text_font->font_atlas.activate(GL_TEXTURE0);
        font_indi.bind();
    }

    void render_context::full_unbind()
    {
        abstractgl::unbind_texture();
        font_indi.unbind();
        font_vao.unbind();
    }

    void render_context::set_start(int x, int y)
    {
        start.x = x + (text_font->widest_glyph_size / 2),
        start.y = y - text_font->highest_glpyh_size;
    }

    void render_context::set_projection(glm::fmat4 projection)
    {
        font_program.use();
        glUniformMatrix4fv(glGetUniformLocation(font_program.get_id(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }

    void render_context::generate_indexes()
    {
        std::vector<uint> indices(6*CHARACTER_RENDER_LIMIT);
        indices.resize(6*CHARACTER_RENDER_LIMIT);
        unsigned int offset = 0;
		for (long int i = 0; i < 6*CHARACTER_RENDER_LIMIT; i += 6)
		{
			indices[i + 0] = 2 + offset;
			indices[i + 1] = 3 + offset;
			indices[i + 2] = 0 + offset;

			indices[i + 3] = 0 + offset;
			indices[i + 4] = 1 + offset;
			indices[i + 5] = 3 + offset;
			offset += 4;
		}

        font_indi.buffer_data(sizeof(uint)*6*CHARACTER_RENDER_LIMIT, &indices[0], GL_STATIC_DRAW);
    }

    void render_context::nextline(float& start_x, float& x2, float& y2)
    {
        x2 = start_x;
        y2 -= text_font->highest_glpyh_size + 5 /*<- padding*/;
    }
}
