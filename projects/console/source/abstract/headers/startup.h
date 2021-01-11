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
    startup.h deals with starting up glfw and
    glew, along with the creation of a window.
*/

#ifndef ABSTRACT_STARTUP_H
#define ABSTRACT_STARTUP_H

#include "textures.h"

#define GLFW_FAILED "unable to startup glfw"
#define GLEW_FAILED "unable to startup glew"
#define WINDOW_CREATION_FAILED "unable to create a window"

namespace abstractgl
{
    // window data - width, height, name
    struct window_data
    {
        window_data();

        // give all members their own data on creation
        window_data(std::string name, int width, int height);

        std::string name;
        int width, height;
    };

    // load the core of opengl
    void hint_to_core(int major, int minor);
        
    // output_parameter - creates a window and will make the windows context current, will return a nullptr if it could not create a window
    void create_window(GLFWwindow*& window, window_data window_data);

    // enable textures that use alpha values when rendered on primtaves to look normal
    void enable_blend();

    // creates a window and will make the windows context current, will return a nullptr if it could not create a window
    GLFWwindow* create_window(window_data window_data);

    // starts glwf  - returns true if it was a successful startup
    bool start_glfw();

    // starts glef - returns true if it was a successful startup
    bool start_glew();

    // output parameter - starts up glfw, creates a window, and then starts up glew
    void startup(GLFWwindow*& window, window_data window_data,  std::string& err, int major, int minor);

    // starts up glfw, creates a window, and then starts up glew
    GLFWwindow* startup(window_data window_data, std::string& err, int major, int minor);
}

#endif // ABSTRACT_STARTUP_H