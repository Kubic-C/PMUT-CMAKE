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
#include <chrono>

void error_callback(int error_code, const char* error_str)
{
    std::cout << error_code << ": " << error_str << '\n';
}

int main()
{
    std::string gl_str; 
    GLFWwindow* window = abstractgl::startup(abstractgl::window_data("hello world", 1000, 1000), gl_str, 4, 0);
    std::cout << gl_str << '\n';

    glfwSetErrorCallback(error_callback);

    abstractgl::enable_blend();

    // start the ft library, extract the font and then pass it to the render context
    abstractgl::ft::lib_ft freetype;
    freetype.start();
    abstractgl::ft::font font;
    if(!font.load_font(freetype, "./misc/fonts/Antonio-Regular.ttf"))
        return 1;

    
    font.compute_font(gl_str);
    std::cout << gl_str << '\n';
    font.end();
    freetype.end();

    // build an compile the shader program
    abstractgl::shader vertex(GL_VERTEX_SHADER);
    vertex.set_shader_src_from_file("./misc/shaders/font.glsl", "vertex");
    abstractgl::shader fragment(GL_FRAGMENT_SHADER);
    fragment.set_shader_src_from_file("./misc/shaders/font.glsl", "fragment");
    std::string ferror, verror, perror;
    verror = vertex.compile();
    ferror = fragment.compile();
    abstractgl::program font_program(perror, vertex, fragment);
    std::cout << ferror << '\n' << verror << '\n' << perror << '\n';
    if(ferror.find("succecced") == std::string::npos)
        return 2;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1000), 0.0f, static_cast<float>(1000));
    font_program.use();
    glUniformMatrix4fv(glGetUniformLocation(font_program.get_id(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // setup the render context
    console::render_context render;
    render.use_font(std::move(font));
    render.use_program(font_program);

    glClearColor(0.0, 0.0, 0.4, 1.0);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT); 

        auto start = std::chrono::high_resolution_clock::now();

        render.print(glm::vec2(0, 900), glm::vec3(1.0f, 0.5f, 0.5f), 1.0f, std::string(__DATE__));

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        using namespace std::chrono_literals;
        std::cout << duration.count()*1000 << '\n';

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
