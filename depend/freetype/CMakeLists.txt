

add_library(lib-freetype STATIC "include/ft2build.h" "include/freetype/freetype.h")

#setting the linker tangy | https://stackoverflow.com/questions/61235133/cmake-can-not-determine-linker-language-for-target-c
set_target_properties(lib-freetype PROPERTIES LINKER_LANGUAGE CXX)

find_package(Freetype REQUIRED)

target_link_libraries(lib-freetype PUBLIC ${FREETYPE_LIBRARIES})

#for files inside of the include dir
target_include_directories(lib-freetype PRIVATE  "include")

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(lib-freetype PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
