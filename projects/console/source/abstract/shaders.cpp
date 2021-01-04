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

#include "headers/shaders.h"

namespace abstractgl
{
    // shader method definitions
    shader::shader(unsigned int type)
        : type(type), id(glCreateShader(type))
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
            this will read through the file given
            and will on start reading the file if
            the @ character and the shader name are 
            on the same line and it will exit going 
            the file(completly stop reading) if the
            @ character, the shader name and the word
            "end"(shader name + " end") are on the same 
            line(once it gets to it)
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
}