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

#include "console/headers/text.h"
#include "HLnetwork/headers/base.h"

int main()
{
    std::string gl_err;
    GLFWwindow* window;
    abstractgl::startup(window, abstractgl::window_data("render test",
         1000, 1000), gl_err, 3, 3);
    std::cout << gl_err << '\n';

    if(!window)
    {
        return -2;
    }

    abstractgl::set_pixel_restriction(1);

    FT_Library lib_ft;
    if(!abstractgl::ft::startup(&lib_ft))
    {
        std::cout << "could not start freetype\n";
        return -1;
    }

    std::string font_err;
    console::lib_test_console();
    
    //std::cout << font_err << '\n';
    //test_font.compute_characters(0, 128, font_err);
    //std::cout << font_err << '\n';

   // console::render::bind_font(&test_font);
/*
    console::render::startup(
        "./release/misc/shaders/font.glsl", 1000, 1000);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        console::render::render_text("this is a test", 
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1000.f/2, 1000.f/2), 1);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
*/
    return 0;
}