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

#include "headers/shaders.h"

namespace abstractgl
{
    // shader method definitions
    shader::shader(unsigned int type)
        : id(glCreateShader(type)), type(type)
    {
    }

    unsigned int shader::get_id()
    {
        return this->id;
    }

    bool shader::set_shader_src_from_file(std::string dir, std::string shader_name)
    {
        std::ifstream shader_file(dir);
        if(shader_file.bad() || !shader_file.is_open())
        {
            return false;
        }

        /*
            goes through every line of file

            if the character '@' and the shader_name
            is present on the same line it will begin
            reading and adding the file lines to shader_source

            if the character '@', the shader_name, and the word "end"
            are all on the same line it will stop reading and exit the
            file
        */
        bool start_reading = false;
        std::string line = "";
        while(std::getline(shader_file, line))
        {
            if(line.find("@") != std::string::npos)
            {
                if(line.find(shader_name) != std::string::npos)
                    start_reading = !start_reading;
                else if(line.find(shader_name + " end") != std::string::npos)
                    break;
            }
            else if(start_reading)
                shader_source += line + '\n';
        }

        c_shader_source = (char*)shader_source.c_str();
        shader_file.close();
        return true;
    }

    std::string shader::compile()
    {
        glShaderSource(id, 1, &c_shader_source, NULL);
        glCompileShader(id);
        
        int success;
        std::vector<char> info_log(DEFAULT_VBUFFER_SPACE); // reserve space for 1024 characters
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, DEFAULT_VBUFFER_SPACE, NULL, info_log.begin().base()); // is info_log.begin()._Ptr(); for windows?
            return "--- compilation of shader(id: " + std::to_string(id) + ") failed ---\n"
                                     + std::string(info_log.begin(), info_log.end());
        }

        return "compilation of shader(id: " + std::to_string(id) + ") succecced\n";
    }
    
    void shader::delete_s()
    {
        glDeleteShader(id);
    }

    // program method definitions
    program::program()
        : id(glCreateProgram())
    {
    }

    unsigned int program::get_id()
    {
        return this->id;
    }

    void program::attach(shader shader)
    {
        glAttachShader(id, shader.get_id());
    }
    
    std::string program::link()
    {
        glLinkProgram(id);
		int success;
        std::vector<char> info_log(DEFAULT_VBUFFER_SPACE); // reserve space for 1024 characters
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, DEFAULT_VBUFFER_SPACE, NULL, info_log.begin().base()); // is info_log.begin()._Ptr(); for windows?
			return "--- compilation of program(id: " + std::to_string(id) + ") failed ---\n"
                                         + std::string(info_log.begin(), info_log.end());
		}

		return "compilation of program(id: " + std::to_string(id) + ") succecced\n";
    }

    void program::use()
    {
        glUseProgram(id);
    }

    void program::delete_p()
    {
        glDeleteProgram(id);
    }

    program compile_shaders(std::string dir, std::string vert_name, std::string frag_name)
    {
        shader vertex(GL_VERTEX_SHADER);
        vertex.set_shader_src_from_file(dir, vert_name);
        std::string verror = vertex.compile();

        shader fragment(GL_FRAGMENT_SHADER);
        fragment.set_shader_src_from_file(dir, frag_name);
        std::string ferror = fragment.compile();

        std::string perror;
        program program_(perror, vertex, fragment);
        std::cout << "program:\n"  << perror 
                  << "\nvertex:\n"   << verror 
                  << "\nfragment:\n" << ferror << '\n';
                  
        return program_;
    }
}