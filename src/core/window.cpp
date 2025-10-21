#include "window.h"

Window::Window(int width, int height, const char* title)
    : _width(width), _height(height), _title(title)
{
    glfwInit();

    _ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(_ptr);
    glfwSetWindowUserPointer(_ptr, this);

    glfwSetWindowCloseCallback(_ptr, [](GLFWwindow* window) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (win->_closeCallback) {
            win->_closeCallback();
        }
    });

    glfwSetFramebufferSizeCallback(_ptr, [](GLFWwindow* window, int width, int height) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (win->_resizeCallback) {
            win->_resizeCallback(width, height);
        }
    });
}

Window::~Window()
{
    glfwDestroyWindow(_ptr);
    glfwTerminate();
}

void Window::update()
{
    glfwPollEvents();
}

void Window::present()
{
    glfwSwapBuffers(_ptr);
}

void Window::setCloseCallback(std::function<void()> cb)
{
    _closeCallback = cb;
}

void Window::setResizeCallback(std::function<void(int, int)> cb)
{
    _resizeCallback = cb;
}
