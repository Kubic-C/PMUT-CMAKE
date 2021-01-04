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

    void texture::activate(unsigned int slot)
    {
        glActiveTexture(slot); // activate the texture unit first before binding texture
		bind();
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

     void set_flip_images_on_load()
     {
         static bool flip = false;
         stbi_set_flip_vertically_on_load(!flip);
     }
}