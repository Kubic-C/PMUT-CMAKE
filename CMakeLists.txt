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

cmake_minimum_required(VERSION "3.12")
project(PMUT)

set(BUILD_LINUX TRUE)

if(BUILD_LINUX) #expects x11 not wayland, NOTE: if your using wayland, linux may freeze entirely
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lglfw3 -lGLU -lGL -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -std=c++17")
elseif(BUILD_WINDOWS) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lglfw3 -lGLU -lGL -std=c++17")
endif()

#PMUT(PORTER MULTI USE TERMINAL) - networking, file manipulation, and live app manipulation

#EXTERNAL
add_subdirectory(depend/asio)
add_subdirectory(depend/stbi_image)

#INTERNAL
add_subdirectory(projects/console)
add_subdirectory(projects/base)
add_subdirectory(projects/HLnetwork)
add_subdirectory(projects/pmut)