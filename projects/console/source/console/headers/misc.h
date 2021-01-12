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
    misc.h
    defines functions that print
    data onto the console screen.
*/

#ifndef CONSOLE_MISC_H
#define CONSOLE_MISC_H

#include "manager.h"
#include <chrono>

#define PROMPTING_USER "[PMUT]"
#define DISPLAYING_INFO "<PMUT>"

// RGB *color or mix of color* 3 paremeters

#define COLOR_RED_3P      1.0f, 0.0f, 0.0f
#define COLOR_GREEN_3P    0.0f, 1.0f, 0.0f
#define COLOR_BLUE_3P     0.0f, 0.0f, 1.0f
#define COLOR_AQUA_3P     0.0f, 1.0f, 1.0f
#define COLOR_YELLOW_3P   1.0f, 1.0f, 0.0f

namespace console
{
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
        void end(manager& console_manager);

    private:
        long double longest_frametime = 0.0L;
        long double shortest_frametime = 100.0L;
        std::chrono::duration<long double> frametime;
        std::chrono::time_point<std::chrono::high_resolution_clock> ft_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> ft_end;
    };
}

#endif // CONSOLE_MISC_H