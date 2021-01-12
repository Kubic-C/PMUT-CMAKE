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

#include "headers/console_data.h"

int main()
{
    bool is_good = false;
    console::manager console_test("manager test", 1000, 1000, is_good);
    if(!is_good)
        return -1;

    console_test.bind();

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

    console_test.print_m(console::modifier::perma_mod, 5, COLOR_YELLOW_3P,
                glGetString(GL_VERSION), '\n');

    glfwSwapInterval(1);

    pmut::timer ft_timer;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(console_test.window))
    {
        ft_timer.start();

        console_test.print(PROMPTING_USER, console::modifier::non_static_mod, 0, COLOR_GREEN_3P);

        console_test.print_m(console::modifier::non_static_mod, 0, COLOR_RED_3P,
                console_test.active_input, '\n');

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); 

        console_test.poll();

        glfwSwapBuffers(console_test.window);

        /* process events, if any */
        glfwPollEvents();

        ft_timer.end(console_test);
    }

    return 0;
}

/* TODO or MAYBE OPTIMIZE

    - any way to put the two for loops into one in 
    projects/console/source/abstract/external.cpp - font::compute_chars() 

*/