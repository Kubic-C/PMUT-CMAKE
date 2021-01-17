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

#include "headers/app.h"
#include <cassert>

namespace pmut
{

    void load_font(stringref dir_to_font, int size)
    {
        abstractgl::ft::lib_ft freetype;
        freetype.start();
    
        if(!data::font.load_font(freetype, 0, size, dir_to_font))
        {
            data::font.end();
            freetype.end();
            exit_app(-2);
            return;
        }
    
        std::cout << "font is now in use\n";

        std::string failed_glpyhs = data::font.compute_font();
        std::cout << failed_glpyhs << '\n';
    
        data::font.end();
        freetype.end();
    }

    void exit_app(int exit_code_a)
    {
        data::exit_code = exit_code_a;
        flags::exit_app = true;
    }

    void startup(
        stringref name, 
        int width,
        int height, 
        stringref dir_to_font, 
        stringref dir_to_shaders, 
        stringref vertex_name, 
        stringref fragment_name
    )   
    {
        bool good = false;
        data::console = new console::manager(name, width, height, good);
        if(!good)
        { 
            exit_app(-1);
            return;
        }

        data::console->bind();

        load_font(dir_to_font, 20);
        if(flags::exit_app)
            return;

        data::font_program = 
            abstractgl::compile_shaders(dir_to_shaders, vertex_name, fragment_name);

        data::renderer = new console::render_context;
        data::renderer->use_font(data::font);
        data::renderer->use_program(data::font_program);
        data::console->use_render_context(*data::renderer);
        data::console->set_all_callbacks();

        abstractgl::enable_blend();

        add_base_commands();
    }

    void cleanup()
    {
        delete data::renderer;
        delete data::console;
        wait_for_end_of_command();
    }

    int app()
    {
        data::console->print_m(console::modifier::perma_mod, 5, COLOR_PURPLE_3P,
                PMUT_NAME, '\n');

        data::console->print_m(console::modifier::perma_mod, 5, COLOR_YELLOW_3P,
                glGetString(GL_VERSION), '\n');

        data::console->set_enter_callback(call_command);

        glfwSwapInterval(1);
        timer loop_timer;
        while(!flags::exit_app && !glfwWindowShouldClose(data::console->window))
        {
            loop_timer.start();

            // render here
            glClear(GL_COLOR_BUFFER_BIT); 

            data::console->print(PROMPTING_USER, console::modifier::non_static_mod, 0, COLOR_YELLOW_3P);

            data::console->print_m(console::modifier::non_static_mod, 0, COLOR_WHITE_3P,
                data::console->get_input() + '_', '\n');

            data::console->poll();

            end_command();

            // show new renders
            glfwSwapBuffers(data::console->window);

            // events
            glfwPollEvents();
            loop_timer.end();
        }

        cleanup();

        std::cout << "exiting with code: " << data::exit_code << '\n';
        return data::exit_code;
    }
}