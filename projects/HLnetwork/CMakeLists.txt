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
