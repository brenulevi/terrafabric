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

    bool isFullscreen() { return _isFullscreen; }
    
    void setFullscreen(bool fullscreen);
    inline void setOnCloseCallback(const std::function<void()>& callback) { _onClose = callback; }
    inline void setOnResizeCallback(const std::function<void(int, int)>& callback) { _onResize = callback; }

private:
    GLFWwindow* _ptr;
    int _width;
    int _height;
    int _lastWidth;
    int _lastHeight;
    const char* _title;

    bool _isFullscreen;

    std::function<void()> _onClose;
    std::function<void(int, int)> _onResize;
};