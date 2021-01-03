#include "headers/vertex_objects.h"

namespace abstract
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