cmake_minimum_required(VERSION 3.16)

project(ood_game LANGUAGES CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(rpg ${SOURCES})

target_compile_features(rpg PRIVATE cxx_std_20)

target_compile_options(rpg PRIVATE
    -Wall
    -Wextra
)
