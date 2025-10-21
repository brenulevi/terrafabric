cmake_minimum_required(VERSION 3.20)

project(TerraFabric VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)

add_executable(terrafabric
    src/main.cpp

    src/core/application.h
    src/core/application.cpp
    src/core/window.h
    src/core/window.cpp
    src/core/assetmanager.h
    src/core/assetmanager.cpp

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

    external/glad/src/glad.c
)

target_link_libraries(terrafabric PRIVATE glfw)

target_include_directories(terrafabric PRIVATE
    src
    external/glfw/include
    external/glad/include
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