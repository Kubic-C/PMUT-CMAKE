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
    font::font(FT_Library& Library)
        :  lib_ft(lib_ft)
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
}