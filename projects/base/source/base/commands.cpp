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

#include "headers/commands.h"
#include <algorithm>

namespace pmut
{
    command_gaurd::~command_gaurd()
    {
        flags::join_thread = true;
    }

    void run(stringref name)
    {
        if(!data::command_thread)
            data::command_thread = new std::thread(data::commands[name].cmd);
        else
            data::console->print("cannot create thread; a command is already running\n", console::modifier::static_mod, -1, COLOR_RED_3P);
    }

    void _end_command()
    {
        data::command_thread->join();
        delete data::command_thread;
        // set command_thread to null to indicate no command is running
        data::command_thread = nullptr; 
        flags::join_thread = false;
        // clear out the commands prevoius data
        data::cmd_local::name.clear();
        data::cmd_local::args.clear();
        data::cmd_local::opts.clear();
    }

    void end_command()
    {
        if(flags::join_thread)
        {
            _end_command();
        }
    }

    void wait_for_end_of_command()
    {
        if(data::command_thread) // if command not done
        {
            _end_command();
        }
    }

    bool is_command_valid(stringref command_name)
    {
        if(data::commands.find(command_name) == data::commands.end())
            return false;
        else
            return true;
    }

    bool is_args_opts_valid(stringref command_name, std::vector<std::string>& arg_names, std::vector<std::string>& opt_names)
    {
        if(arg_names.size() != data::commands[command_name].valid_args.size())
        {
            log_err("too many or to little arguments: ", arg_names.size(), '\n');
            return false;
        }

        for(std::string& arg : data::commands[command_name].valid_args) // check if ALL arguments exist
        { 
            if(std::find(std::begin(arg_names), std::end(arg_names), arg) == arg_names.end())
            {
                log_err("could not find argument: [", arg, "]\n");
                return false;
            }
        }

        if(!opt_names.size())
            return true;

        if(size_t size = opt_names.size() >  data::commands[command_name].valid_opts.size())
        {
            log_err("too many options: ", size+1, '\n');
            return false;
        }

        std::vector<std::string>& valid_opts = data::commands[command_name].valid_opts;
        for(std::string& opt : opt_names) // check if the given options are valid
        {
            if(std::find(std::begin(valid_opts), std::end(valid_opts), opt) == valid_opts.end())
            {
                log_err("the given option is invalid: <", opt, ">\n");
                return false;
            }
        }

        return true;
    }

    bool set_args_opts(
        stringref command,
        std::vector<std::string>& arg_names,
        std::vector<std::string>& opt_names,
        std::vector<std::string>& arg_datas,
        std::vector<std::string>& opt_datas
    )
    {
        if(!is_args_opts_valid(command, arg_names, opt_names))
        {
            return false;
        }

        if(!arg_names.size() && !opt_names.size()) // no opt names or no arg names
            return true;

        // arg_names is ALWAYS equal(in size) to arg_datas
        for(size_t i = 0; i < arg_names.size(); i++)
        {   
            data::cmd_local::args[arg_names[i]] = arg_datas[i];
        }

        // opt_names is ALWAYS(in size) equal to opt_datas
        for(size_t i = 0; i < opt_names.size(); i++)
        {   
            data::cmd_local::opts[opt_names[i]] = opt_datas[i];
        }

        return true;
    }
}