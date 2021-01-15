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

#include "headers/parser.h"
#include <numeric>

namespace pmut
{
    std::string extract(std::string& string, char start, char end)
    {
        // *start* some string *end*
        size_t start_i = string.find(start);
        size_t end_i = string.find(end);
    
        if(start_i == std::string::npos)
        {
            return BAD_EXTRACT;
        }

        if(end_i == std::string::npos)
        {
            return BAD_EXTRACT;
        }

        start_i++;
        std::string substr = string.substr(start_i, end_i - start_i);
        start_i--; end_i++;
        string.erase(start_i, end_i - start_i);
        return substr;
    }

    std::string get_command(std::string& string)
    {
        std::string final = "";
        if((final = extract(string, '{', '}')) == BAD_EXTRACT)
        {
            log_err("command box does not have beginning or ending curly brackets\n");
        }

        return final;
    }

    std::vector<std::string> get_args(std::string& string)
    {
        std::vector<std::string> arguments = {};
        std::string arg = "";
        while((arg = extract(string, '[', ']')) != BAD_EXTRACT)
            arguments.push_back(arg);

        return arguments;
    }

    std::vector<std::string> get_opts(std::string& string)
    {
        std::vector<std::string> options = {};
        std::string opt = "";
        while((opt = extract(string, '<', '>')) != BAD_EXTRACT)
            options.push_back(opt);

        return options;
    }

    std::vector<std::string> extract_box_datas(std::vector<std::string>& boxes, bool& good)
    {
       std::vector<std::string> box_datas = {};
       for(std::string box : boxes)
       {
           size_t pos = box.find(':');
           if(pos == std::string::npos)
           {
               log_err("(datas)the equal operator ':' was not found in box: ", box, '\n');
               good = false;
               break;
           }

           box_datas.push_back(box.substr(pos+1));
       }

       return box_datas;
    }

    std::vector<std::string> extract_box_names(std::vector<std::string>& boxes, bool& good)
    {
       std::vector<std::string> box_names = {};
       for(std::string box : boxes)
       {
           size_t pos = box.find(':');
           if(pos == std::string::npos)
           {
               log_err("(names)the equal operator ':' was not found in box: ", box, '\n');
               good = false;
               break;
           }

           box_names.push_back(box.substr(0, pos));
       }

       return box_names;
    }

    void call_command(stringref str)
    {
        std::string copy = str;

        std::string command = "";
        if((command = get_command(copy)) == BAD_EXTRACT)
            return;

        if(data::commands.find(command) == data::commands.end())
        {
            log_err("uknown command: {", command, "} \n");
            return;
        }

        std::vector<std::string> args, arg_names, arg_datas;
        std::vector<std::string> opts, opt_names, opt_datas;

        args = get_args(copy);
        opts = get_opts(copy);
        bool good[4] = { true, true, true, true };
        arg_datas = extract_box_datas(args, good[0]);
        opt_datas = extract_box_datas(opts, good[1]);
        arg_names = extract_box_names(args, good[2]);
        opt_names = extract_box_names(opts, good[3]);
        int is_good = good[0] + good[1] + good[2] + good[3]; // i tried std::accumulate, it flopped :P;
        if(is_good != 4)
            return;

        if(!set_args_opts(command, arg_names, opt_names, arg_datas, opt_datas))
        {
            return;
        }

        run(command);
    }
}