add_executable(pmut source/main.cpp)

#INTERNAL
target_link_libraries(pmut PRIVATE lib-console)
target_link_libraries(pmut PRIVATE lib-hlnetwork)