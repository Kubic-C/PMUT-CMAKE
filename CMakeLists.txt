cmake_minimum_required(VERSION "3.12")
project(PMUT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw3 -lGLU -lGL -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl")

#PMUT(PORTER MULTI USE TERMINAL) - networking, file manipulation, and live app manipulation

#EXTERNAL
add_subdirectory(depend/asio)

#INTERNAL
add_subdirectory(projects/console)
add_subdirectory(projects/HLnetwork)
add_subdirectory(projects/pmut)