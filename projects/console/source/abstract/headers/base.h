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

#define DEFAULT_BUFFER_TARGET GL_ARRAY_BUFFER

//namespace abstract for all abstract opengl objects
namespace abstract
{
}

#endif //BASE_ABSTREACT_H