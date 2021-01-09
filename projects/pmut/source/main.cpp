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

#include "console/headers/render.h"
#include "HLnetwork/headers/base.h"
#include <chrono>

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    std::cout << message << '\n';
}


int main()
{
    std::string gl_str; 
    GLFWwindow* window = abstractgl::startup(abstractgl::window_data("hello world", 800, 640), gl_str, 4, 0);
    std::cout << gl_str << '\n';

    if(!window)
    {
        std::cout << "failed to create window\n";
        return 1;
    }

    abstractgl::enable_blend();

    // start the ft library, extract the font and then pass it to the render context //
    abstractgl::ft::lib_ft freetype;
    freetype.start();

    abstractgl::ft::font font;
    if(!font.load_font(freetype, "./misc/fonts/ye.ttf"))
        return 1;
    
    font.compute_font(gl_str);
    std::cout << gl_str;

    font.end();
    freetype.end();

    // build an compile the shader program
    abstractgl::program font_program = 
            abstractgl::compile_shaders("./misc/shaders/font.glsl", "vertex", "fragment");

    // setup the render context
    console::render_context render;
    render.use_font(std::move(font));
    render.use_program(font_program);

    glClearColor(0.0, 0.0, 0.4, 1.0);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); 

        int x, y;
        glfwGetWindowSize(window, &x, &y);
        glViewport(0, 0, x, y);
        render.set_start(10, y);
        render.set_projection(glm::ortho(0.0f, static_cast<float>(x), 0.0f, static_cast<float>(y)));

        render.full_bind();
        render.print(std::string((const char*)glGetString(GL_VERSION)), glm::vec3(sin(glfwGetTime()), 0.5f, 0.5f), 1.0f);
        render.print("[ENGINE] -- test ---", glm::vec3(sin(glfwGetTime()), 0.5f, 0.5f), 1.0f);
        render.print_poll();
        render.full_unbind();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
