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

#include "console/headers/include.h"
#include "HLnetwork/headers/base.h"

int main()
{
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    bool is_good = false;
    console::manager console_test("manager test", 1000, 1000, is_good);
    if(!is_good)
        return -1;

    abstractgl::enable_blend();

    // start the ft library, extract the font and then pass it to the render context //
    abstractgl::ft::lib_ft freetype;
    freetype.start();

    abstractgl::ft::font font;
    if(!font.load_font(freetype, 0, 30, "./misc/fonts/__font.ttf"))
    {
        font.end();
        freetype.end();
        return -1;
    }

    std::string failed_glpyhs = font.compute_font();
    std::cout << failed_glpyhs << '\n';

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

    console_test.print((char*)glGetString(GL_VERSION), console::modifier::perma_mod, 2, COLOR_YELLOW_3P);

    glfwSwapInterval(1);

    console::timer ft_timer;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(console_test.window))
    {
        ft_timer.start();

        console_test.print(PROMPTING_USER, console::modifier::non_static_mod, 2, 0.5f, 1.0f, 0.1f, false);
        console_test.print(console_test.active_input + '~', console::modifier::non_static_mod, 2, 1.0, 1.0f, 1.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); 

        console_test.poll();

        glfwSwapBuffers(console_test.window);

        /* process events, if any */
        glfwPollEvents();

        ft_timer.end();
    }

    return 0;
}
