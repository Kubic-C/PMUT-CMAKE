

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

