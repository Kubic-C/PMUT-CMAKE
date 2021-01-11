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

#creating the STATIC library | https://stackoverflow.com/questions/60592615/how-would-i-include-asio-library-using-cmake#comment107198393_60592615
add_library(lib-asio STATIC "include/asio.hpp")

#setting the linker tangy | https://stackoverflow.com/questions/61235133/cmake-can-not-determine-linker-language-for-target-c
set_target_properties(lib-asio PROPERTIES LINKER_LANGUAGE CXX)

#using the ASIO standalone library ;)
target_compile_options(lib-asio PRIVATE ASIO_STANDALONE)

#for files inside of the include dir
target_include_directories(lib-asio PRIVATE  "include")

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(lib-asio PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

#link asio to the threading library
target_link_libraries(lib-asio PRIVATE pthread) # pthread for linux

