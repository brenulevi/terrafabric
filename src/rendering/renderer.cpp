#include "renderer.h"

Renderer::Renderer()
{
    gladLoadGL();

    glViewport(0, 0, 800, 600);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
}
