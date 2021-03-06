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
    command_def.h lists all "base" commands
*/

#ifndef BASE_COMMAND_DEF_H
#define BASE_COMMAND_DEF_H

#include "parser.h"

namespace pmut
{   
    namespace commands
    {
        // exit the console with code n, default for code is 0
        void exit();

        // clear the console
        void clear();

        // echo to the console
        void echo();
    }

    void add_base_commands();
}

#endif // BASE_COMMAND_DEF_H