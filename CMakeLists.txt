cmake_minimum_required(VERSION 3.16)
project("Ants")
file(GLOB SRC_FILES ./src/*)
include_directories(./include)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC -lsfml-graphics 
                                             -lsfml-window
                                             -lsfml-system)
