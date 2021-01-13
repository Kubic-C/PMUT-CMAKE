#
# PMUT (Porter Multi Use Terminal) is a multi use command line,
# that can in the future do networking, file manipulation, and
# live app manipulation.
# 
# PMUT  Copyright (C) 2021 Sawyer Porter#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.#
#

# high level networking using asio standalone

file(GLOB_RECURSE SOURCES_HLNETWORK
    source/HLnetwork/headers/*.h
    source/HLnetwork/*.cpp
)

add_library(
    hlnetwork
    ${SOURCES_HLNETWORK}
)

#EXTERNAL 
target_link_libraries(hlnetwork PUBLIC lib-asio)

#INTERAL
target_link_libraries(hlnetwork PUBLIC base)

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(hlnetwork PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")
