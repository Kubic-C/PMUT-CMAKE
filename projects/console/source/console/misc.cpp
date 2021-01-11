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

#include "headers/misc.h"

namespace console
{
    void timer::start()
    {
        ft_start = std::chrono::high_resolution_clock::now();
    }   

    void timer::end()
    {
        ft_end = std::chrono::high_resolution_clock::now();
        frametime = ft_end - ft_start;
        if(frametime.count() > longest_frametime)
            longest_frametime = frametime.count();
        else if(frametime.count() < shortest_frametime)
            shortest_frametime = frametime.count();

        current_manager->print(DISPLAYING_INFO + std::string(" frametime(ft): ") + std::to_string(frametime.count()*1000),
                        modifier::non_static_mod, 2, COLOR_AQUA_3P);

        current_manager->print(DISPLAYING_INFO + std::string(" shortest ft: ") + std::to_string(shortest_frametime*1000),
                        modifier::non_static_mod, 2, COLOR_AQUA_3P);

        current_manager->print(DISPLAYING_INFO + std::string(" longest ft: ") + std::to_string(longest_frametime*1000),
                        modifier::non_static_mod, 2, COLOR_AQUA_3P);
    }
}