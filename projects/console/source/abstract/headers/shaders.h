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
    along with this program.  If not, see <https://www.gnu.org/licenses/>

*/
#ifndef ABSTRACT_SHADERS_H
#define ABSTRACT_SHADERS_H

#include "vertex_objects.h"

namespace abstractgl
{
    /*
        shaders are "half-programs" that run on the GPU
        and can change the color and positions
        of the vertexes. but in order to run on 
        the GPU they need to be put in a program object.
    */
   class shader
   {
   public:
        // create a new shader
        shader(uint32_t type);

    public: // methods ---
        // this will get the id of a file
        uint32_t get_id();
        
        // get the shader source code from a file, returns a boolean value, false mean it could not get the shader, true means it was able to get the shader
        bool set_shader_src_from_file(std::string dir, std::string shader_name);

        // this will compile the shader and will return a string that gives the status of the compilation
        std::string compile();

        // delete the shader
        void delete_s();

    private:
        uint32_t id; // id of the shader given by opengl
        uint32_t type; // the type of the shader
        std::string shader_source; // the shader source code
        char* c_shader_source; // allows compatabilty with c functions - c str version of shader source code
   };

    /*
        programs are made up of shaders and are capable
        of running on the GPU
    */
    class program
    {
    public:
        // create a new program
        program();

        // add all shaders inside of program
        template<typename ... shaders_p>
        program(std::string& err, shaders_p& ... shaders_a)
        : id(glCreateProgram())
        {
            ((attach(shaders_a)), ... );
            err = link();
            ((shaders_a.delete_s()), ... );
        }

    public: // methods ---
        // link the program
        std::string link();

        // attach all the shaders that you want inside the final programs
        void attach(shader shader);

        // deletes the progrma
        void delete_p();

        // gets the id of the program
        uint32_t get_id();

        // uses the program/puts the program on the GPU
        void use();

    private:
        uint32_t id;
    };

    // compile both vertex and fragment
    program compile_shaders(std::string dir, std::string vert_name, std::string frag_name);
}

#endif // ABSTRACT_SHADERS_H