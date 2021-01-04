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

#include "headers/external.h"

namespace abstractgl
{
    void set_pixel_restriction(int size)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, size);
    }

     // freetype
    namespace ft 
    {
        bool startup(FT_Library* lib_ft)
        {
            if(FT_Init_FreeType(lib_ft))
            {
                fprintf(stderr, "Could not init freetype library\n");
                return false;
            }

            return true;
        }

        bool new_face(FT_Library lib_ft, std::string dir, glm::ivec2 dim, FT_Face* new_face)
        {
            bool face_bad = FT_New_Face(lib_ft, dir.c_str(), 0, new_face);
            if(!face_bad)
             return face_bad;

            else
            {
                FT_Set_Pixel_Sizes(*new_face, dim.x, dim.y);
                return face_bad;
            }
        }

        FT_GlyphSlot load_char(FT_Face face, char character)
        {
            FT_GlyphSlot glyph = nullptr;
            FT_Load_Char(face, character, FT_LOAD_RENDER);
            return glyph;
        }
    }
}