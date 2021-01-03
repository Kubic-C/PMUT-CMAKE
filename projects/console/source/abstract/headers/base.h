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
    ABSTRACT deals with turning low level opengl into a higher level
    more readable opnegl. vertex buffer objects, vertex array objects, 
    and other opengl objects will be abstracted into classes to make
    code simplier and future optimizations easier
*/

#ifndef BASE_ABSTRACT_H
#define BASE_ABSTRACT_H

// external non-default includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// usual includes
#include <string>
#include <vector>
#include <fstream>

#define DEFAULT_BUFFER_TARGET GL_ARRAY_BUFFER
#define DEFAULT_VBUFFER_SPACE 1024

//namespace abstract for all abstract opengl objects
namespace abstract
{
}

#endif //BASE_ABSTREACT_H