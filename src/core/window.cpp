#include "window.h"

Window::Window(int width, int height, const char* title)
    : _width(width), _height(height), _title(title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _ptr = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
    if (!_ptr)
        throw std::runtime_error("Failed to create GLFW window");

    glfwMakeContextCurrent(_ptr);
    glfwSetWindowUserPointer(_ptr, this);

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
