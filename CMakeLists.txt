cmake_minimum_required(VERSION 3.10)

project(gl0b)

file(GLOB SOURCES "src/gl0b.cpp" "src/**/*.cpp")

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(gl0b ${SOURCES})
target_link_libraries(gl0b PRIVATE GLEW::GLEW glfw)