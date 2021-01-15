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

        opts = { "c" }, args = {};
        data::commands["exit"] = (command){commands::exit, args, opts};

        opts = {}, args = {};
        data::commands["clear"] = (command){commands::clear, args, opts};

        opts = {}, args = { "str" };
        data::commands["echo"] = (command){commands::echo, args, opts};
    }

    namespace commands
    {
        void exit()
        {
            command_gaurd gaurd;
            if(data::cmd_local::opts.find("c") != data::cmd_local::opts.end())
            {
                try { data::exit_code = std::stoi(data::cmd_local::opts["c"]); } 
                catch(std::exception& x) { log_err(x.what(), " error", '\n');  return; }
            }

            flags::exit_app = true;
        }

        void clear()
        {
            command_gaurd gaurd;
            data::console->mtx.lock();
            data::console->clear_output_buffer();
            data::console->mtx.unlock();
        }
        
        void echo()
        {
            command_gaurd gaurd;
            data::console->print(data::cmd_local::args["str"] + '\n', console::modifier::static_mod, -1, COLOR_WHITE_3P);         
        }
    }
}