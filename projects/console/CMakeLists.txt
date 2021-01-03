# console deals with input and output
# this console is made with GLFW & GLEW (OpenGL)


#dir to console ------
set(console_dir "source/console")

#all headers(.h) in the console dir
set(console_headers 
"${console_dir}/headers/base.h"
)

#all source(.cpp) files in the console dir
set(console_sources 
"${console_dir}/base.cpp"
)

#dir to abstract ------
set(abstract_dir "source/abstract")

#all headers(.h) in the abstract dir
set(absract_headers 
"${abstract_dir}/headers/base.h"
"${abstract_dir}/headers/vertex_objects.h"
)

#all source(.cpp) in the abstract dir
set(absract_sources
"${abstract_dir}/base.cpp"
"${abstract_dir}/vertex_objects.cpp"
)


add_library(
    lib-console
    ${console_headers}
    ${console_sources}
    ${absract_headers}
    ${absract_sources}
)

#EXTERNAL
#OPENGL
find_package(OpenGL REQUIRED)
target_link_libraries(lib-console PRIVATE OpenGL::GL)
#GLFW
find_library(lib-glfw3path libglfw3.a)
target_link_libraries(lib-console PRIVATE ${lib-glfw3path})
#GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message(STATUS "GLEW was found")
    target_link_libraries(lib-console PRIVATE GLEW::GLEW)
else()
    message(STATUS "GLEW could not be found")
endif()
#DLL
target_link_libraries(lib-console PRIVATE ${CMAKE_DL_LIBS})

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(lib-console PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source")

# makes this possible: #include "exmaple.h", instead of doing #include "../../../console/source/headers/exmaple.h"
target_include_directories(lib-console PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")
