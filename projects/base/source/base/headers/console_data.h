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
    console_data.h, timers, colors, and other console related  data,
*/

#ifndef CONSOLE_DATA_H
#define CONSOLE_DATA_H

#include "flags.h"
#include <chrono>

#define DISPLAYING_INFO "{PMUT}"
#define PROMPTING_USER "[PMUT]<<"

// COLOE *color or mix of color* 3 paremeters

#define COLOR_RED_3P      1.0f, 0.0f, 0.0f
#define COLOR_BLUE_3P     0.0f, 0.0f, 1.0f
#define COLOR_AQUA_3P     0.0f, 1.0f, 1.0f
#define COLOR_WHITE_3P    1.0f, 1.0f, 1.0f
#define COLOR_GREEN_3P    0.0f, 1.0f, 0.0f
#define COLOR_YELLOW_3P   1.0f, 1.0f, 0.0f
#define COLOR_PURPLE_3P   1.0f, 0.0f, 1.0f

namespace pmut
{
    namespace data
    {
        extern console::render_context* renderer;
        extern abstractgl::program font_program;
        extern console::manager* console;
        extern abstractgl::ft::font font;
    }

    /*  timer class
     * this will count the
     * time between start()
     * and end() methods, giving 
     * back the frametime
     * 
    */
    class timer
    {
    public: // methods --
        // start timer
        void start();

        // end timer
        void end();

        // restart
        void restart();

    private:
        long double longest_frametime = 0.0L;
        long double shortest_frametime = 100.0L;
        std::chrono::duration<long double> frametime;
        std::chrono::time_point<std::chrono::high_resolution_clock> ft_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> ft_end;
    };

    template<typename ... params>
    void log_err(const params& ... args)
    {
        data::console->print_m(console::modifier::static_mod, -1, COLOR_RED_3P, args...);
    }

    template<typename ... params>
    void log_data(const params& ... args)
    {
        data::console->print_m(console::modifier::static_mod, -1, COLOR_WHITE_3P, args...);
    }
}

#endif // CONSOLE_DATA_H