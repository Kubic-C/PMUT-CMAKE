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
        std::cout << "console lib test" << '\n';
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
                continue;
            }
            else
            {
                character character;
                character.bitmap.load_tex_image(
                    GL_UNSIGNED_BYTE,
                    GL_RED,
                    GL_RED,
                    face->glyph->bitmap.width, 
                    face->glyph->bitmap.rows,
                    face->glyph->bitmap.buffer
                );
                character.bitmap.bind();
                abstractgl::set_default_bitmap_tex_args();

                character.char_id = c;
                character.advance = face->glyph->advance.x;
                character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
                character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);

                char_set[character.char_id] = std::move(character);
            }
        }

        abstractgl::unbind_texture();
        FT_Done_Face(face);
    }

    void font::set_library(FT_Library lib_ft)
    {
        this->lib_ft = lib_ft;
    }

    namespace render
    {
        void startup(std::string dir_to_shader, float width, float height)
        {
            std::string vertex_err, fragment_err, program_err;
            abstractgl::shader vertex(GL_VERTEX_SHADER);
            abstractgl::shader fragment(GL_FRAGMENT_SHADER);

            if(!vertex.set_shader_src_from_file(dir_to_shader, "vertex")  ||
               !fragment.set_shader_src_from_file(dir_to_shader, "fragment"))
            {
                std::cout << dir_to_shader << '\n' <<
                        "is invalid\n";
                return;
            }

            vertex_err = vertex.compile();
            fragment_err = fragment.compile();
            
            font_program.attach(vertex);
            font_program.attach(fragment);

            program_err = font_program.link();

            std::cout << vertex_err   << '\n'
                      << fragment_err << '\n' 
                      << program_err  << '\n';

            set_projection_dim(width, height);

            font_vao.bind();
            font_vbo.gen(GL_ARRAY_BUFFER);
            font_vbo.buffer_data(sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

            font_vbo.bind();
            font_vao.vertex_attrib_pointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            font_vbo.unbind();
        }

        void set_projection_dim(float width, float height)
        {
            projection = glm::ortho(0.0f, width, 0.0f, height); 
            font_program.use();
            glUniformMatrix4fv(glGetUniformLocation(font_program.get_id(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        }

        void use_font(font& new_font)
        {
            current_font = new_font;
        }

        void render_text(render_data render_data)
        {
            font_program.use();
            auto location = glGetUniformLocation(font_program.get_id(), "textColor");
            glUniform3f(
                location,
                render_data.color.x,
                render_data.color.y,
                render_data.color.z
            );

            for(auto c : render_data.str)
            {
                character& ch = current_font.char_set[c];

                float xpos = render_data.position.x + ch.bearing.x * render_data.scale;
                float ypos = render_data.position.y - (ch.bearing.x - ch.bearing.y) * render_data.scale;

                float w = ch.size.x * render_data.scale;
                float h = ch.size.y * render_data.scale;

                float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 0.0f },            
                    { xpos,     ypos,       0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },

                    { xpos,     ypos + h,   0.0f, 0.0f },
                    { xpos + w, ypos,       1.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 0.0f }           
                };

                ch.bitmap.bind();
                font_vbo.update_buffer(sizeof(vertices), vertices);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                render_data.position.x += (ch.advance >> 6) * render_data.scale;
            }

            font_vao.unbind();
            abstractgl::unbind_texture();
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