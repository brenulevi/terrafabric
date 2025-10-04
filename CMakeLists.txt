cmake_minimum_required(VERSION 3.10)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/spdlog)

project(terrafabric)

set(CMAKE_CXX_STANDARD 17)

add_executable(terrafabric
    src/main.cpp
    src/game.cpp
    src/window.cpp
    src/logger.cpp
    src/renderer.cpp
    src/resourcemanager.cpp
    src/shader.cpp
    src/buffer.cpp
    src/vertexarray.cpp

    dependencies/glad/src/glad.c
)

target_compile_definitions(terrafabric PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(terrafabric PRIVATE glfw spdlog)

target_include_directories(terrafabric PRIVATE
    dependencies/glad/include
    dependencies/glm/
    dependencies/stb/
)

if(WIN32)
    target_link_libraries(terrafabric PRIVATE opengl32)
else()
    target_link_libraries(terrafabric PRIVATE GL)
endif()

# add_custom_command(
#     TARGET terrafabric POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:terrafabric>/assets
#     COMMENT "Copying assets to output directory")