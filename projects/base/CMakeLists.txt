#
#   PMUT (Porter Multi Use Terminal) is a multi use command line,
#   that can do networking, file manipulation, and
#   live app manipulation.
#   
#   PMUT  Copyright (C) 2021 Sawyer Porter
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

file(GLOB_RECURSE SOURCES_COMMANDS
    source/base/headers/*.h
    source/base/*.cpp
)

add_library(
    base
    ${SOURCES_COMMANDS}
)

target_link_libraries(base PUBLIC console)

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(base PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")