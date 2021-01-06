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

void error_callback(int error_code, const char* error_def)
{
    std::cout << error_code << ": " << error_def << '\n';
}

int main()
{
     if(console::gl_libs.error_exit_code)
        return console::gl_libs.error_exit_code;

    // with out glBlend, textures cannot 'blend'
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set the window information
    console::gl_libs.set_window_size(glm::ivec2(1000, 1000));
    console::gl_libs.set_window_title("render test");
    
    // set the error callback, this makes getting error alot more easier
    glfwSetErrorCallback(&error_callback);
    
    // this is the font the rendering interface will use
    console::font test_font;
    test_font.set_library(console::gl_libs.lib_ft);

    // default for opengl is 4, but freetype needs it to 1
    abstractgl::set_byte_restriction(1);

    // load the bitmap that the rendering interface will use
    std::string font_err;
    test_font.load_bitmap("../pmut/misc/fonts/Antonio-Regular.ttf", font_err);
    std::cout << font_err << '\n';
    if(font_err == FAILED_TO_LOAD_FACE)
        return -1;

    // compute the characters, so load every ASCII character
    test_font.compute_characters(0, 128, font_err);
    std::cout << font_err << '\n';

    // free the ft library since it is no longer needed
    FT_Done_FreeType(console::gl_libs.lib_ft);

    // use the test font
    console::render::use_font(test_font);

    // startup the rendering interface
    console::render::startup(
        "../pmut/misc/shaders/font.glsl", 1000, 1000);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while(!glfwWindowShouldClose(console::gl_libs.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        console::render::render_text("this is a test", 
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1000.f/2, 1000.f/2), 1.0f);

        glfwSwapBuffers(console::gl_libs.window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
