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

// master include
#ifndef ABSTRACT_INCLUDE_H
#define ABSTRACT_INCLUDE_H

#include "external.h"

// to set the version
#define PMUT_GL_VERSION 3, 3

namespace abstractgl
{
    // only use this when global varibles that use opengl
    // are initialized before main
    struct init
    {   
        GLFWwindow* window = nullptr;
        FT_Library lib_ft = nullptr;
        int error_exit_code = 0;

        init()
        {
            std::string gl_err;
            abstractgl::startup(window, abstractgl::window_data("--- NOT INITIALIZED ---", 10, 10), gl_err, PMUT_GL_VERSION);

            if(gl_err.size() != 0)
            {
                std::cout << gl_err << '\n';
                error_exit_code = -1;
                return;
            }

            if(!abstractgl::ft::startup(&lib_ft))
            {
                std::cout << "could not start freetype\n";
                int error_exit_code = -2;
                return;
            }
        }

        inline void set_window_size(glm::ivec2 dim)
        {
            glViewport(0, 0, dim.x, dim.y);
            glfwSetWindowSize(window, dim.x, dim.y);
        }

        inline void set_window_title(std::string title)
        {
            glfwSetWindowTitle(window, title.c_str());
        }
    };
}

#endif // ABSTRACT_INCLUDE_H