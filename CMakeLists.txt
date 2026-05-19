cmake_minimum_required(VERSION 3.10)

project(ParticleSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(app
    src/main.cpp
)

target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

target_link_libraries(app PRIVATE
    glfw
    OpenGL::GL
    controller
)

add_subdirectory(src)
