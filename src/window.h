#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <functional>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void pollEvents();
    void swapBuffers();

    inline void setOnCloseCallback(const std::function<void()>& callback) { _onClose = callback; }
    inline void setOnResizeCallback(const std::function<void(int, int)>& callback) { _onResize = callback; }

private:
    GLFWwindow* _ptr;
    int _width;
    int _height;
    const char* _title;

    std::function<void()> _onClose;
    std::function<void(int, int)> _onResize;
};