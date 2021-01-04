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
#include <map>


#define FAILED_TO_LOAD_FACE "failed to load face"
#define FAILED_TO_LOAD_GLYPH "failed to load glyph: "

namespace console
{
    struct character
    {
        char char_id; // character id ASCII
        abstractgl::texture bitmap;
        glm::ivec2 size;
        glm::ivec2 bearing;
        unsigned int advance;
    };

    /*
        font will load a single texture
    */
    class font
    {
    public:
        font(FT_Library& lib_ft);

    public: // methods ---
        // load a face/bitmap
        void load_bitmap(std::string dir, std::string& err);

        // parse data - will pre compute everything
        void compute_characters(int min, int max, std::string& err);

    protected:
        std::map<char, character> char_set;
        FT_Face face;
        FT_Library& lib_ft;
    };
    
}
 
#endif // CONSOLE_BITMAP_H