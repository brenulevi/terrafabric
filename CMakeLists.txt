cmake_minimum_required(VERSION 3.20)

project(TerraFabric VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_executable(terrafabric
    src/main.cpp

    src/core/application.h
    src/core/application.cpp
    src/core/window.h
    src/core/window.cpp
    src/core/assetmanager.h
    src/core/assetmanager.cpp
    src/core/input.h
    src/core/input.cpp

    src/rendering/renderer.h
    src/rendering/renderer.cpp
    src/rendering/shader.h
    src/rendering/shader.cpp
    src/rendering/vertexbuffer.h
    src/rendering/vertexbuffer.cpp
    src/rendering/indexbuffer.h
    src/rendering/indexbuffer.cpp
    src/rendering/vertexarray.h
    src/rendering/vertexarray.cpp
    src/rendering/bufferlayout.h
    src/rendering/bufferlayout.cpp
    src/rendering/mesh.h
    src/rendering/mesh.cpp
    src/rendering/texture.h
    src/rendering/texture.cpp
    src/rendering/uniformbuffer.h
    src/rendering/uniformbuffer.cpp
    
    src/components/transform.h
    src/components/transform.cpp
    src/components/camera.h
    src/components/camera.cpp

    src/game/player.h
    src/game/player.cpp
    src/game/cube.h
    src/game/cube.cpp
    src/game/chunk.h
    src/game/chunk.cpp
    src/game/world.h
    src/game/world.cpp

    external/glad/src/glad.c
    external/stb_image/src/stb_image.cpp
)

target_link_libraries(terrafabric PRIVATE glfw glm)

target_include_directories(terrafabric PRIVATE
    src
    external/glfw/include
    external/glad/include
    external/stb_image/include
    external/glm/include
)

target_compile_definitions(terrafabric PRIVATE
    GLFW_INCLUDE_NONE
)

add_custom_command(
    TARGET terrafabric POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:terrafabric>/assets
    COMMENT "Copying assets to output directory"
)