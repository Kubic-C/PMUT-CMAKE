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

#ifndef TEXTURES_H
#define TEXTURES_H

#include "shaders.h"

namespace abstractgl
{
    typedef void(*default_tex_args)();

    // this holds info about an image
    struct image
    {
        unsigned char* image;
        int width, height, nr_channels;
    };

    // binds to zero
    void unbind_texture();

    // this will activate a texture slot, remember that use GL_TEXTURE, not a 1, 0, or 2 for example.
    void activate_texture(unsigned int slot);

    /*
        textures in opengl make it possible to take images
        and apply them to shapes in a window.
    */
    class texture
    {
    public:
        // generate a texture object without loading a image
        texture();

        // generate a texture object 
        texture(std::string dir_to_image, default_tex_args def_tex_args);

    public: // methods ---
        // bind the texture
        void bind();

        // unbind the texture
        void unbind();

        // glTexImage
        void allocate(
            unsigned int type,
            unsigned int internal_format, 
            unsigned int format,
            int width, 
            int height,
            void* pixels
        );

        // glTexSubImage, space HAS to be already allocated for this to work
        void load_data(
            unsigned int type,
            unsigned int xoffset, 
            unsigned int yoffset, 
            unsigned int format,
            int width, 
            int height,
            void* pixels
        );

        // load an image, returns false for bad file, and true for successful load
        // note: this does not set the glTex parameters, you will have to set those
        // your self, or call set_default_tex_args;
        bool load_image(std::string dir_to_image);

        // gets the info about an image(if loaded)
        image get_image();

        // this will activate the texture into a slot
        void activate(unsigned int slot);

    private:
        unsigned int id;
        image image_texture;
    };

    // this will fill the args for textures
    void set_default_tex_args();

    // this will fill the args for bitmaps
    void set_default_bitmap_tex_args();

    // this will make stbi flip images on load, calling this once will flip images on load, calling this again will stop that.
    void set_flip_images_on_load();
}

#endif //TEXTURES_H