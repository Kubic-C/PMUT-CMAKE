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

#ifndef NETWORK_BASE_H
#define NETWORK_BASE_H

#include "base/headers/command_def.h"
#include <asio.hpp>

namespace hlnet
{
    void lib_test();
}

#endif // NETWORK_BASE_H

/*
    TCP/UDP SERVER & CLIENT ASYNC

    - have to define a function that will read all data until no more is being sent, then return.
    
*/