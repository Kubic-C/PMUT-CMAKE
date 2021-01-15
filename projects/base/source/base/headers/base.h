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
    base project holds global/cross-project varibles such as the
    console manager, general app data, and flags. .
*/

#ifndef BASE_BASE_H
#define BASE_BASE_H

#include "console/headers/include.h"

typedef const std::string& stringref;

namespace pmut
{
    namespace data
    {
        extern int exit_code;
    }
}

#endif // BASE_BASE_H