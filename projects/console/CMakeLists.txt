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

# console deals with input and output
# this console is made with GLFW & GLEW (OpenGL)


#dir to console ------
set(console_dir "source/console")

file(GLOB_RECURSE SOURCES
    source/abstract/headers/*.h
    source/abstract/*.cpp
    source/console/headers/*.h
    source/console/*.cpp
)

add_library(
    console
    ${SOURCES}
)

# EXTERNAL
# OPENGL 
find_package(OpenGL REQUIRED)
target_link_libraries(console PRIVATE OpenGL::GL)
# GLFW
find_library(lib-glfw3path libglfw3.a)
target_link_libraries(console PRIVATE ${lib-glfw3path})
# GLEW
find_package(GLEW REQUIRED)
target_link_libraries(console PRIVATE GLEW::GLEW)

# DLL
target_link_libraries(console PRIVATE ${CMAKE_DL_LIBS})

# STBI IMAGE
target_link_libraries(console PRIVATE lib-stbi_image)

# FREETYPE
find_package(Freetype REQUIRED)
target_link_libraries(console PRIVATE ${FREETYPE_LIBRARIES})
target_include_directories(console PUBLIC ${FREETYPE_INCLUDE_DIRS})
message(STATUS "${FREETYPE_LIBRARIES}\n-- ${FREETYPE_INCLUDE_DIRS}")

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(console PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source")

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")
