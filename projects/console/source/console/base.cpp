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

#include "headers/base.h"

namespace console
{
}

std::string convert_to_string(const std::string& str)
{
    return str;
}

std::string convert_to_string(const char* str)
{
    return std::string(str);
}

std::string convert_to_string(char* str)
{
    return std::string(str);
}

std::string convert_to_string(const unsigned char* str)
{
    return std::string((const char*)str);
}

std::string convert_to_string(unsigned char* str)
{
    return std::string((char*)str);
}

std::string convert_to_string(char char_)
{
    return std::string() += char_;
}