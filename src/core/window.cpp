#include "window.h"

Window::Window(int width, int height, const char* title)
    : _width(width), _height(height), _title(title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _ptr = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    if (!_ptr)
        throw std::runtime_error("Failed to create GLFW window");

    glfwMakeContextCurrent(_ptr);
    glfwSwapInterval(0);
    glfwSetWindowUserPointer(_ptr, this);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(_ptr, (mode->width - _width) / 2, (mode->height - _height) / 2);

    glfwSetWindowCloseCallback(_ptr, [](GLFWwindow* window) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->_onClose();
    });

    glfwSetFramebufferSizeCallback(_ptr, [](GLFWwindow* window, int width, int height) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        win->_width = width;
        win->_height = height;

        win->_onResize(width, height);
    });
}

Window::~Window()
{
    glfwDestroyWindow(_ptr);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_ptr);
}

void Window::setFullscreen(bool fullscreen)
{
    _isFullscreen = fullscreen;


    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (fullscreen)
    {
        _lastWidth = _width;
        _lastHeight = _height;
        glfwSetWindowMonitor(_ptr, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(_ptr, nullptr, (mode->width - _lastWidth) / 2, (mode->height - _lastHeight) / 2, _lastWidth, _lastHeight, 0);
    }
}
