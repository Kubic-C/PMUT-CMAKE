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

#ifndef ABSTRACT_EXTERNAL_H
#define ABSTRACT_EXTERNAL_H

#include "startup.h"

#define FT_LIB_STARTUP_ERROR "could not start the freetype(2) library\n"
#define FT_LIB_STARTUP_GOOD "startup of freetype(2) library succecced\n"
#define FT_GLYPH_ERROR "failed to load gylph"

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

        struct character 
        {
            std::vector<float> tex_coords; // texture coords of the character on the font atlas, use indicies
            float bearingy_minus_sizey;
            glm::ivec2   size;      // Size of glyph
            glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
            uint32_t advance;   // Horizontal offset to advance to next glyph
        };

        // starts up the freetype library
        bool startup(FT_Library* lib_ft);

        // FT_New_Face
        bool new_face(FT_Library lib_ft, std::string dir, glm::ivec2 dim, FT_Face* new_face);

        // FT_Load_Char
        bool load_char(FT_Face& face, char character);

        // this is a simple wrapper for FT_Library types
        class lib_ft
        {
        public:
            lib_ft();
            ~lib_ft();

        public: // methods ---
            // start freetype, returns true for good startup, return false for bad startup
            bool start();

            // end/cleanup/close freetype
            void end();

        public: // members ---
            FT_Library lib;

        };

        // font allows a more simpler way to abstract .tff or .bff font files
        // whilst still using the freetype library
        class font
        {
        public:
            font();
            ~font();

        public: // methods ---
            // load a .tff or .bff file, true for good, false for bad
            bool load_font(lib_ft& lib_ft, int f_width, int f_height, std::string dir);

            // compute the indivual characters
            std::string compute_font();

            // cleanup the font
            void end();

        public:
            std::map<char, character> char_set; // all characters
            texture font_atlas; // all textures
            int highest_glpyh_size = 0; // height of the highest glyph 
            int widest_glyph_size = 0; // widest glyph size
            FT_Face face; // FT_Face the font
        };
    }
}

#endif // ABSTRACT_EXTERNAL_H