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

#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>
#include "headers/textures.h"

namespace abstractgl
{

    void unbind_texture()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void activate_texture(uint32_t slot)
    {
        glActiveTexture(slot);
    }

    // texture method definitions

    texture::texture()
    {
        glGenTextures(1, &id);
    }

    texture::texture(std::string dir_to_image, default_tex_args def_tex_args)
    {
        glGenTextures(1, &id);
        bind();
        def_tex_args();
        load_image(dir_to_image);
    }

    void texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    bool texture::load_image(std::string dir_to_image)
    {
        bind();

        image_texture.image = stbi_load(dir_to_image.c_str(), &image_texture.width, &image_texture.height, &image_texture.nr_channels, 0); 
        if(!image_texture.image)
            return false;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_texture.width, image_texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_texture.image);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image_texture.image);
        unbind();

        return true;
    }

    void texture::activate(uint32_t slot)
    {
        activate_texture(slot); // activate the texture slot first before binding texture
		bind();
    }

    void texture::allocate(
        uint32_t type,
        uint32_t internal_format, 
        uint32_t format,
        int width, 
        int height,
        void* pixels)
    {
        bind();
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            internal_format,
            width,
            height,
            0,
            format,
            type,
            pixels
        );
        unbind();
    }

    void texture::load_data(
        uint32_t type,
        uint32_t xoffset, 
        uint32_t yoffset, 
        uint32_t format,
        int width, 
        int height,
        void* pixels)
    { 
        bind();
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            xoffset,
            yoffset,
            width,
            height,
            format,
            type,
            pixels
        );
        unbind(); 
    }

    image texture::get_image()
    {
        return image_texture;
    }

    // function definitions

    void set_default_tex_args()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void set_default_bitmap_tex_args()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

     void set_flip_images_on_load(bool set_flag)
     {
         stbi_set_flip_vertically_on_load(set_flag);
     }
}