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
        font();
        font(FT_Library lib_ft);

    public: // methods ---
        // load a face/bitmap
        void load_bitmap(std::string dir, std::string& err);

        // parse data - will pre compute everything
        void compute_characters(int min, int max, std::string& err);

        // sets the ft library member
        void set_library(FT_Library lib_ft);

    public: // members ---
        std::map<char, character> char_set;
        FT_Face face;
        FT_Library lib_ft;
    };

    void lib_test_console();

    namespace render
    {
        // render_data holds some additional data of how a string should get print onto the screen
        struct render_data
        {
            std::string str; // this is what will get output to the screen
            glm::vec3 color; // this will control the color over the text
            glm::vec2 position; // this will control the position of the string on screen
            float scale; // this controls the size of the text
        };

        // render_inline_data holds some additional data of how a string should get print onto the screen
        // this can print in a  horizontal list with other inline data, but you cannot control the position.
        // example:
        // some data 
        // some other data
        // === THIS IS WITH RENDER DATA(this lets you control the position) ===
        // some data
        //                     some other data
        struct render_inline_data
        {
            std::string str; // this is what will get output to the screen
            glm::vec3 color; // this will control the color over the text
        };
        
        // static extern
        // the render will use whatever fount is currently 'bound'
        extern font current_font;

        // this is the render shader program, is uses ./release/misc/shaders/font.glsl'
        extern abstractgl::program font_program;

        // this is the vertex array object responsible for holding vbo which hold data about text
        extern abstractgl::vertex_array font_vao;

        // holds raw data of whatever character position, this allows char position data to go onto the GPU
        extern abstractgl::vertex_buffer font_vbo;

        // projection matrix for rendering text
        extern glm::mat4 projection;

        // this will startup the renderer
        void startup(std::string dir_to_shader, float width, float height);

        // this will set the projection to a new screen width height
        void set_projection_dim(float width, float height);

        // this will use a new font, using a new font will of course overwrite the new one
        void use_font(font& new_font);

        // render "render data"
        void render_text(render_data render_data);

         // render "render data"
        void render_text(std::string text, glm::vec3 color, glm::vec2 pos, float scale);

        // render inline data poll
        void render_inline_text(render_inline_data render_inline_data);
    }
}
 
#endif // CONSOLE_BITMAP_H