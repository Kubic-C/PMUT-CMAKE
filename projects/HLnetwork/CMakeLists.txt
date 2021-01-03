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

#dir to network
set(network_dir "source/HLnetwork")

#all headers(.h) in the console dir
set(console_headers 
"${network_dir}/headers/base.h"
)

#all source(.cpp) files in the console dir
set(console_sources 
"${network_dir}/base.cpp"
)

add_library(
    lib-hlnetwork
    ${console_headers}
    ${console_sources}
)

#EXTERNAL 
target_link_libraries(lib-hlnetwork PUBLIC lib-asio)

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(lib-hlnetwork PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")
