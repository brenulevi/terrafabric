#pragma once

#include <glad/glad.h>

class Renderer
{
public:
    Renderer();

    void clear();

    void onResize(int width, int height);
};