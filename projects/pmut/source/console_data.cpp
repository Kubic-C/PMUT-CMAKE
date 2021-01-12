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

namespace pmut
{
     void timer::start()
    {
        ft_start = std::chrono::high_resolution_clock::now();
    }   

    void timer::end(console::manager& console_manager)
    {
        ft_end = std::chrono::high_resolution_clock::now();
        frametime = ft_end - ft_start;
        if(frametime.count() > longest_frametime)
            longest_frametime = frametime.count();
        else if(frametime.count() < shortest_frametime)
            shortest_frametime = frametime.count();

        console_manager.print_m(console::modifier::non_static_mod, 2, COLOR_AQUA_3P,
            DISPLAYING_INFO, " frametime(ft): ", frametime.count()*1000, '\n',
            DISPLAYING_INFO, " shortest ft: ", shortest_frametime*1000, '\n',
            DISPLAYING_INFO, " longest ft: ", longest_frametime*1000, '\n'
        );
    }
}
