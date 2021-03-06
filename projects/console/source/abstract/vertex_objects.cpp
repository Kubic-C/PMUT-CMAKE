/*
    PMUT (Porter Multi Use Terminal) is a multi use command line,
    that can do networking, file manipulation, and
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
    vertex_buffer::vertex_buffer(uint32_t id_, uint32_t type_)
        : id(id_), type(type_)
    { 
    }

    vertex_buffer::vertex_buffer(uint32_t type_)
    {
        gen(type_);
    }

    vertex_buffer::vertex_buffer()
    {
    }
    
    void vertex_buffer::set_type(uint32_t type)
    {
       this->type = type;
    }


    void vertex_buffer::buffer_data(
       long size,         
       const void* data,  
       uint32_t usage 
    )
    {
        bind();
        glBufferData(type, size, data, usage);
        unbind();
    }
 
    void vertex_buffer::update_buffer(uint32_t size, void* data)
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

    void vertex_buffer::gen(uint32_t new_type)
    {
        type = new_type;
        glGenBuffers(1, &id);
    }

    void vertex_buffer::delete_b()
    {
        glDeleteBuffers(1, &id);
    }

    // vertex array definitions
    void vertex_array::vertex_attrib_pointer(
        uint32_t index,
        uint32_t size,  
        uint32_t type,  
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

    vertex_array::vertex_array(uint32_t id)
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

    void vertex_array::delete_a()
    {
        glDeleteVertexArrays(1, &id);
    }
}