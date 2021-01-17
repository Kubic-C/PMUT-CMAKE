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
    defines commands, i.e. how they run, and how they are stored
*/

#ifndef BASE_COMMANDS_H
#define BASE_COMMANDS_H

#include "console_data.h"
#include <thread>
#include <map>

namespace pmut
{
    typedef void(*cmd_fun_ptr)();  

    struct command
    {
        cmd_fun_ptr cmd;
        std::vector<std::string> valid_args; 
        std::vector<std::string> valid_opts;
    };

    namespace data
    {
        extern std::unordered_map<std::string, command> commands;
        extern std::thread* command_thread;

        namespace cmd_local
        {
            extern std::string name;
            extern std::map<std::string, std::string> args;
            extern std::map<std::string, std::string> opts;
        }
    }

    // command_gaurd sets join_thread in the deconstructor
    class command_gaurd
    {
    public:
        command_gaurd();
        ~command_gaurd();

    };

    // run a command async
    void run(stringref name);

    // end a command in command_thread. no safety
    void _end_command();

    // try and end a command in command_thread
    void end_command();

    // this will wait for a command to be done
    void wait_for_end_of_command();

    // check if the command is valid, true for yes, false for no
    bool is_command_valid(stringref command_name);

    // check if the arguments and options provided by the user are valid. true for yes, false for no
    bool is_args_opts_valid(stringref command_name, std::vector<std::string>& args, std::vector<std::string>& opts);

    // this will set the cmd_local::args and cmd_local::opts
    bool set_args_opts(
        stringref command,
        std::vector<std::string>& arg_names,
        std::vector<std::string>& opt_names,
        std::vector<std::string>& arg_datas,
        std::vector<std::string>& opt_datas
    );
}

#endif // BASE_COMMANDS_H