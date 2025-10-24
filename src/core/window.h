#pragma once

#include <GLFW/glfw3.h>
#include <functional>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void update();
    void present();

    void setCloseCallback(std::function<void()> cb);
    void setResizeCallback(std::function<void(int, int)> cb);

    GLFWwindow* getPtr();

private:
    GLFWwindow* _ptr;
    int _width;
    int _height;
    const char* _title;
    std::function<void()> _closeCallback;
    std::function<void(int, int)> _resizeCallback;
};