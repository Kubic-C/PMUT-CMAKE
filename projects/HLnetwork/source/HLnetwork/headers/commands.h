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
    commands.h of the HLnetwork library defines networking commands
*/

#ifndef HLNETWORK_COMMANDS_H
#define HLNETWORK_COMMANDS_H

#include "base.h"

namespace hlnet
{
    void add_network_commands();

    namespace commands
    {
        // write to the ip and port given
        void write_to();
    }
}

#endif // HLNETWORK_COMMANDS_H