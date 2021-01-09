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

#include "console/headers/manager.h"
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
    bool is_good = false;
    console::manager console_test("manager test", 1000, 1000, is_good);
    if(!is_good)
        return -1;

    abstractgl::enable_blend();

    // start the ft library, extract the font and then pass it to the render context //
    abstractgl::ft::lib_ft freetype;
    freetype.start();

    std::string gl_str;
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
    render.use_font(font);
    render.use_program(font_program);
    console_test.use_render_context(render);
    console_test.set_all_callbacks();

    console_test.print((char*)glGetString(GL_VERSION), console::modifier::perma_mod, 2, 1.0f, 1.0f, 0.0f);


    glClearColor(0.0, 0.0, 0.4, 1.0);
    while (!glfwWindowShouldClose(console_test.window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); 

        auto start = std::chrono::high_resolution_clock::now();
        console_test.print("[PMUT]" + console_test.active_input, console::modifier::non_static_mod, 0, 1.0f, 1.0f, 1.0f);
        console_test.poll();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        console_test.print("[PMUT] frametime: " + std::to_string(duration.count()*1000), console::modifier::non_static_mod, 1, 1.0f, 0.6f, 0.6f);

        /* Swap front and back buffers */
        glfwSwapBuffers(console_test.window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
