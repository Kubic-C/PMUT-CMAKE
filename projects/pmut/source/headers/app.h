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

/*
    app.h defines a main loop for pmut to run in.
*/

#ifndef PMUT_APP_H
#define PMUT_APP_H

#include "base.h"

namespace pmut
{
    // global data
    namespace data
    {
        extern console::render_context* renderer;
        extern abstractgl::program font_program;
        extern abstractgl::ft::font font;
        extern console::manager* console;
        extern int exit_code;
    }

    // load a font
    void load_font(stringref dir_to_font, int size);

    // exit pmut
    void exit_app(int exit_code);

    // startup pmut
    void startup(
        stringref name, 
        int width,
        int height, 
        stringref dir_to_font, 
        stringref dir_to_shaders, 
        stringref vertex_name, 
        stringref fragment_name
    );

    // cleanup pmut
    void cleanup();

    //  app_loop() defines a loop
    int app();

    void early_frame();

    void frame();

    void late_frame();
}

#endif // PMUT_APP_H