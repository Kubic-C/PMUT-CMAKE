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
    parser.h turns strings into a command name, args, and opts
*/

#ifndef BASE_PARSER_H
#define BASE_PARSER_H

#include "commands.h"

/*
    user input should look like this when calling a command:
    {command name} [argument] [argument]... <option> <option>...
        cmd box       arg boxes ---           opt boxes ---
*/

#define BAD_EXTRACT "[[bad]]"

namespace pmut
{
    // extract anything in between start and end, also remvoing it from the string
    std::string extract(std::string& string, char start, char end);

    // get the command name located in {command name}
    std::string get_command(std::string& string);

    // get the arguments located in [argument] [argument]..
    std::vector<std::string> get_args(std::string& string);

    // get the options located in <option> <option>...
    std::vector<std::string> get_opts(std::string& string);

    // extract box datas located in <option name : data>...
    std::vector<std::string> extract_box_datas(std::vector<std::string>& boxes, bool& good);

    // extract box names located in <option name : data>...
    std::vector<std::string> extract_box_names(std::vector<std::string>& boxes, bool& good);

    // takes a users input and calls the coorelating command
    void call_command(stringref str);
}

#endif // BASE_PARSER_H