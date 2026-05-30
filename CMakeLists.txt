cmake_minimum_required(VERSION 3.16)

project(ood_game LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(rpg ${SOURCES})

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
set(INCLUDE_DIRS "")
foreach(header ${HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)
target_include_directories(rpg PRIVATE ${INCLUDE_DIRS})

target_compile_features(rpg PRIVATE cxx_std_20)

target_compile_options(rpg PRIVATE
    -Wall
    -Wextra
)
