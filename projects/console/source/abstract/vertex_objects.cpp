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

#include "headers/vertex_objects.h"

namespace abstractgl
{
    // vertex buffer definitions
    vertex_buffer::vertex_buffer(unsigned int id_, unsigned int type_)
        : id(id_), type(type_)
    { 
    }

    vertex_buffer::vertex_buffer(unsigned int type_)
       : type(type_)
    {
        glGenBuffers(1, &id);
    }

    vertex_buffer::vertex_buffer()
    {
    }
    
     void vertex_buffer::set_type(unsigned int type)
     {
        this->type = type;
     }

    void vertex_buffer::buffer_data(
       long size,         
       const void* data,  
       unsigned int usage 
    )
    {
        bind();
        glBufferData(type, size, data, usage);
        unbind();
    }
 
    void vertex_buffer::update_buffer(unsigned int size, void* data)
    {
        bind();
        glBufferSubData(type, 0, size, data);
        unbind();
    }

    void vertex_buffer::bind()
    {
        glBindBuffer(type, id);
    }

    void vertex_buffer::unbind()
    {
        glBindBuffer(DEFAULT_BUFFER_TARGET, 0); 
    }

    // vertex array definitions
    void vertex_array::vertex_attrib_pointer(
        unsigned int index,
        unsigned int size,  
        unsigned int type,  
        unsigned char norm, 
        int stride,         
        const void* offset 
    )
    {
        bind();
        glVertexAttribPointer(index, size, 
                          type, norm, stride, offset);
        glEnableVertexAttribArray(index);
        unbind();
    }

    vertex_array::vertex_array(unsigned int id)
        : id(id)
    {
    }

    vertex_array::vertex_array()
    {
        glGenVertexArrays(1, &id);
    }

    void vertex_array::bind()
    {
        glBindVertexArray(id);
    }   

     void vertex_array::unbind()
    {
        glBindVertexArray(0);
    }   
}