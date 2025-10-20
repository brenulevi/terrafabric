#include "window.h"

Window::Window(int width, int height, const char* title)
{
}

Window::~Window()
{
}

void Window::update()
{
}

void Window::present()
{
}

void Window::setCloseCallback(std::function<void()> cb)
{
}

void Window::setResizeCallback(std::function<void(int, int)> cb)
{
}
