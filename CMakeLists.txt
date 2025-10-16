cmake_minimum_required(VERSION 3.18)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/spdlog)

project(terrafabric)

set(CMAKE_CXX_STANDARD 17)

add_executable(terrafabric
    src/main.cpp

    src/core/game.h src/core/game.cpp
    src/core/window.h src/core/window.cpp
    src/core/resourcemanager.h src/core/resourcemanager.cpp
    src/core/input.h src/core/input.cpp
    src/core/raycast.h src/core/raycast.cpp

    src/logging/logger.h src/logging/logger.cpp

    src/rendering/renderer.h src/rendering/renderer.cpp
    src/rendering/shader.h src/rendering/shader.cpp
    src/rendering/buffer.h src/rendering/buffer.cpp
    src/rendering/vertexarray.h src/rendering/vertexarray.cpp
    src/rendering/texture.h src/rendering/texture.cpp

    src/components/transform.h
    src/components/camera.h
    src/components/mesh.h

    src/game/chunk.h src/game/chunk.cpp
    src/game/player.h src/game/player.cpp
    src/game/world.h src/game/world.cpp

    dependencies/glad/src/glad.c
)

target_compile_definitions(terrafabric PRIVATE
    GLFW_INCLUDE_NONE
    STB_IMAGE_IMPLEMENTATION
)

target_link_libraries(terrafabric PRIVATE glfw spdlog)

target_include_directories(terrafabric PRIVATE
    dependencies/glad/include
    dependencies/glm/
    dependencies/stb/

    src/
)

if(WIN32)
    target_link_libraries(terrafabric PRIVATE opengl32)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    target_link_libraries(terrafabric PRIVATE GL)
endif()

add_custom_command(
    TARGET terrafabric POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:terrafabric>/assets
    COMMENT "Copying assets to output directory")