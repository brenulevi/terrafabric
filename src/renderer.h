#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdexcept>

#include "resourcemanager.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();

    void setViewport(int x, int y, int width, int height);

    void onResize(int width, int height);
};