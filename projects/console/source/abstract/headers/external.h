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
    math.h deals with vector math and other related
    graphics math. I am not including GLM 
    since the math that this projects requires is not
    much
*/

#ifndef ABSTRACT_MATH_H
#define ABSTRACT_MATH_H

#include "startup.h"

namespace abstractgl
{
    // glPixelStorei(GL_UNPACK_ALIGNMENT, size);
    void set_byte_restriction(int size);

    // freetype
    namespace ft 
    {
        /* FT How to
            text rendering done - bad
        */

        // starts up the freetype library
        bool startup(FT_Library* lib_ft);

        // FT_New_Face
        bool new_face(FT_Library lib_ft, std::string dir, glm::ivec2 dim, FT_Face* new_face);

        // FT_Load_Char
        bool load_char(FT_Face& face, char character);
    }
}

#endif // ABSTRACT_MATH_H