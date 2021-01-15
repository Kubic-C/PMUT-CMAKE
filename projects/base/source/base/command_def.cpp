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

#include "headers/command_def.h"

namespace pmut
{
    void add_base_commands()
    {
        std::vector<std::string> args;
        std::vector<std::string> opts;

        args = {};
        opts = {};
        data::commands["exit"] = (command){commands::exit, args, opts};
    }

    namespace commands
    {
        void exit()
        {
            command_gaurd gaurd;
            flags::exit_app = true;
        }
    }
}