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
    abstraction for vertex buffer objects and vertex array objects
*/
#ifndef ABSTRACT_VERTEX_OBJECTS_H
#define ABSTRACT_VERTEX_OBJECTS_H

#include "base.h"

namespace abstractgl
{
    /*
        vertex buffer(vertex buffer object(s) - vbo) are buffers
        that are stored on the gpu usually in an vertex array 
        object
    */
    class vertex_buffer
    {
    public: 
        // pass a already existing vbo
        vertex_buffer(uint32_t id, uint32_t type); 

        // make a new vbo
        vertex_buffer(uint32_t type);

        // give no type
        vertex_buffer();
        
    public: // methods ---
        // set the type of buffer i.e. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY etc.
        void set_type(uint32_t type);

        // tell opengl to put data inside of the buffer
        void buffer_data(
            long size,          // size of the data to be put in the vbo
            const void* data,   // a pointer to the data to be put in the vbo
            uint32_t usage  // see https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
        ); 
 
        // this update the data on the gpu(replacing whatever was there)
        void update_buffer(uint32_t size, void* data);

        // binds the buffer
        void bind();

        // unbinds the buffer
        // note: the code 'glBindBuffer(GL_ARRAY_BUFFER, 0)' 
        // can be called anywhere and will unbind whatever
        // vbo is bound wehther or not you call this method
        void unbind();

        // this will generate a new buffer
        void gen(uint32_t type);

        // delete the buffer
        void delete_b();

    private:
        uint32_t id; // the vbo's id given by opengl
        uint32_t type; // the type of data stored in the buffer
    };

    /*
        vertex array(vertex array object(s) - vao) store vbos in 
        an array, the vbos can then be access by GLSL shaders
    */
   class vertex_array
   {
   public:
        // pass an already existing vao
        vertex_array(unsigned int id); 

        // generate a new vao
        vertex_array();
   public: // methods ---
        // tell opengl how the data shall be read inside of the 
        // currently bound vbo, also adding the vbo to the vao
        void vertex_attrib_pointer(
            uint32_t index, // where in the array
            uint32_t size,  // 
            uint32_t type,  // GL_FLOAT, etc.
            unsigned char norm, // is normalized(already a float)
            int stride,         // how many bytes to get to the vertex
            const void* offset  // where should it start
        );
 
        // binds the vao
        void bind();

        // unbinds the vao
        // note: the code 'glBindVertexArray(0)' 
        // can be called anywhere and will unbind whatever
        // vao is bound wehther or not you call this method
        void unbind();

        // delete the buffer
        void delete_a();

   private:
        uint32_t id; // the vao's id given by opengl
   };
} 

#endif // ABSTRACT_VERTEX_OBJECTS_H