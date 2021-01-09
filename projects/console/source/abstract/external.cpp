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
    void set_byte_restriction(int size)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, size);
    }

     // freetype
    namespace ft 
    {
        bool startup(FT_Library* lib_ft)
        {
            if(FT_Init_FreeType(&*lib_ft))
            {
                return true;
            }

            return false;
        }

        bool new_face(FT_Library lib_ft, std::string dir_, glm::ivec2 dim, FT_Face* new_face)
        {
            const char* dir = dir_.c_str();
            bool face_bad = FT_New_Face(lib_ft, dir, 0, new_face);
            if(face_bad)
                return face_bad;

            FT_Set_Pixel_Sizes(*new_face, dim.x, dim.y);
            return face_bad;
        }

        bool load_char(FT_Face& face, char character)
        {
            return FT_Load_Char(face, character, FT_LOAD_RENDER); 
        }

        // lib_ft definitions
        lib_ft::lib_ft()
            : lib(nullptr)
        {
        }

        bool lib_ft::start()
        {
            if (abstractgl::ft::startup(&lib))
            {
                std::cout << FT_LIB_STARTUP_ERROR << '\n';
                return false;
            }

             std::cout << FT_LIB_STARTUP_GOOD << '\n';
            return true;
        }

        void lib_ft::end()
        {
            FT_Done_FreeType(lib);
            lib = nullptr; // i am able to set this to nullptr since FT_Library is FT_LibraryRec_*
        }

        lib_ft::~lib_ft()
        {
            if(lib)
                end();
        }

        // font definitions
        font::font()
        {
        }

        font::~font()
        {
            if(face)
                end();
        }

        bool font::load_font(lib_ft& lib_ft, std::string dir)
        {
            if (abstractgl::ft::new_face(lib_ft.lib, dir, glm::ivec2(0, 30), &face))
            {
                std::cout << "failed to load face from dir: \n" << dir << '\n'; 
                return false;
            }

            return true;
        }

        void font::compute_font(std::string& failed_char)
        {
            // goal of this function is to create a font atlas that looks like this
            // | bitmap | bitmap | bitmap | ...
            // and create a map of std::pair<char, character> the second holding data of
            // where the character is in the font atlas

            // disable byte-alignment restriction
            abstractgl::set_byte_restriction(1);

            // these values control the size of the finished texture atlas
            int atlas_width = 0;
            int atlas_height = 0;

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // load character glyph 
                if (abstractgl::ft::load_char(face, c))
                {
                    failed_char.append(FT_GLYPH_ERROR + c);
                    continue;
                }
                
                // measure the width and the height of every character to dictate the size
                // of the font atlas, but only take the hight of the highest glypgh to
                // fill in the data for atlas_height
                atlas_width += face->glyph->bitmap.width;
                atlas_height = std::max(atlas_height, (int)face->glyph->bitmap.rows);
            }

            // this will go ahead and allocate some space on VRAM/GPU RAM, keep in mind this texture holds no data currently
            font_atlas.allocate(
                GL_UNSIGNED_BYTE,
                GL_RED,
                GL_RED,
                atlas_width,
                atlas_height,
                nullptr // notice that were just allocating space here, not filling data 
            );
            font_atlas.bind();
            set_default_bitmap_tex_args();
            font_atlas.unbind();

            int x = 0;

            // paste the glyph data on to the font atlas
            for(unsigned char c = 0; c < 128; c++)
            {
                if(abstractgl::ft::load_char(face, c))
                    continue;

                // paste the buffer into the font atlas
                font_atlas.load_data(
                    GL_UNSIGNED_BYTE,
                    x,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    face->glyph->bitmap.buffer
                );

                /* --- save the glyph data to a list --- */

                // save this data to be used when printing
                char_set[c].advance = face->glyph->advance.x >> 6; // how far the cursor should move to clear character(stop characters from clipping)
                char_set[c].size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
                char_set[c].bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);


                // we divide it by the width to normalize, since tex coords can only between 0.0, and 1.0
                float tx = (float)x / atlas_width; 

                float tc_width = (float)char_set[c].size.x / atlas_width;
                float tc_height = (float)char_set[c].size.y / atlas_height; 
                char_set[c].tex_coords.resize(12); // resize the glyph to hold the initialization list
                char_set[c].tex_coords = // these are four vertexes(vec2) becuase were are using indicies
                {
                    tx + tc_width , 0,
                    tx            , 0,
                    tx + tc_width , tc_height, 
                    tx            , tc_height,
                };

                // this is required to prevent glyphs from just pasting on top of one another
                x += face->glyph->bitmap.width;
            }

            // generate mip maps for some efficiency
            font_atlas.bind();
            glGenerateMipmap(GL_TEXTURE_2D);
            font_atlas.unbind();

            highest_glpyh_size = atlas_height;

            abstractgl::unbind_texture();
        }

        void font::end()
        {
            FT_Done_Face(face);
            face = nullptr;
        }
    }
}