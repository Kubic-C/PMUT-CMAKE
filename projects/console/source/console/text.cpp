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

#include <iostream>
#include "headers/text.h"

namespace console
{
    void lib_test_console()
    {
        std::cout << "console lib test" << render::current_font << '\n';
    }

    font::font()
        :  lib_ft(nullptr)
    {
    }

    font::font(FT_Library library)
        :  lib_ft(library)
    {
    }

    void font::load_bitmap(std::string dir, std::string& err)
    {
        if(abstractgl::ft::new_face(lib_ft, dir, glm::ivec2(0, 48), &face))
        {
            err = FAILED_TO_LOAD_FACE;
            return;
        }
        else
            return;
    }

    void font::compute_characters(int min, int max, std::string& err)
    {
        for(; min < max; min++)
        {
            char c = min;
            if(abstractgl::ft::load_char(face, c))
            {
                err += std::string(FAILED_TO_LOAD_GLYPH) + c;
        
            }
            else
            {
                character character;
                character.bitmap.bind();
                abstractgl::set_default_bitmap_tex_args();
                character.bitmap.load_sub_image(
                    face->glyph->bitmap.width, 
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.buffer
                );
                character.advance = face->glyph->advance.x;
                character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
                character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
                char_set[character.char_id] = character;
            }
        }

        FT_Done_Face(face);
    }

    namespace render
    {
        void startup(std::string dir_to_shader, float width, float height)
        {
            font_vbo.set_type(GL_ARRAY_BUFFER);

            std::string vertex_err, fragment_err, program_err;
            abstractgl::shader vertex(GL_VERTEX_SHADER);
            abstractgl::shader fragment(GL_FRAGMENT_SHADER);

            vertex.set_shader_src_from_file(dir_to_shader, "vertex");
            fragment.set_shader_src_from_file(dir_to_shader, "fragment");

            vertex_err = vertex.compile();
            fragment_err = fragment.compile();

            font_program.attach(vertex);
            font_program.attach(fragment);

            program_err = font_program.link();

            std::cout << vertex_err   << '\n'
                      << fragment_err << '\n' 
                      << program_err  << '\n';

            set_projection_dim(width, height);
        }

        void set_projection_dim(float width, float height)
        {
            projection = glm::ortho(0.0f, width, 0.0f, height);
            glUniformMatrix4fv(glGetUniformLocation(font_program.get_id(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        }

        void bind_font(font* new_font)
        {
            current_font = new_font;
        }

        void render_text(render_data render_data)
        {
            font& render_font = *current_font;
            
            font_program.use();
            glUniform3f(glGetUniformLocation(font_program.get_id(), "textColor"), 
                            render_data.color.x, render_data.color.y, render_data.color.z);
            font_vao.bind();

            for(char render_char : render_data.str)
            {
                character ch = render_font.char_set[render_char];

                float xpos = render_data.position.x + ch.bearing.x * render_data.scale;
                float ypos = render_data.position.y - (ch.size.y - ch.bearing.y) * render_data.scale;

                float w = ch.size.x * render_data.scale;
                float h = ch.size.y * render_data.scale;

                float vertices[6][4] = 
                {
                    { xpos,     ypos + h,   0.0f, 0.0f },            
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }           
               };

                ch.bitmap.activate(0);
                font_vbo.update_buffer(sizeof(vertices), vertices);
                glDrawArrays(GL_TRIANGLES, 0, 6);

                render_data.position.x += (ch.advance >> 6) * render_data.scale;  // advance is 1/64 pixels. bitshift by 6 to get value in pixels (2^6 = 64)
            }

            font_vao.unbind();
            glBindTexture(GL_TEXTURE_2D, 0);
        }

         // render "render data"
        void render_text(std::string text, glm::vec3 color, glm::vec2 pos, float scale)
        {
            render_data buffer = { text, color, pos, scale };
            render_text(buffer);
        }

        // render inline data poll
        void render_inline_text(render_inline_data render_inline_data)
        {

        }
    }
}