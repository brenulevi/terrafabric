#pragma once

#include <GLFW/glfw3.h>

enum CursorMode
{
    NORMAL = GLFW_CURSOR_NORMAL,
    HIDDEN = GLFW_CURSOR_HIDDEN,
    DISABLED = GLFW_CURSOR_DISABLED
};

class Input
{
public:
    static void initialize();
    static void update();

    inline static bool isKeyHeld(int key) { return _currentKeys[key]; }
    inline static bool isKeyPressed(int key) { return _currentKeys[key] && !_previousKeys[key]; }
    inline static bool isKeyReleased(int key) { return !_currentKeys[key] && _previousKeys[key]; }

    inline static float getMouseX() { return _mouseX; }
    inline static float getMouseY() { return _mouseY; }

    inline static CursorMode getCursorMode() { return _cursorMode; }
    static void setCursorMode(CursorMode mode);


private:
    static bool _currentKeys[GLFW_KEY_LAST];
    static bool _previousKeys[GLFW_KEY_LAST];
    static bool _currentMouseButton[GLFW_MOUSE_BUTTON_LAST];
    static bool _previousMouseButton[GLFW_MOUSE_BUTTON_LAST];
    static float _mouseX;
    static float _mouseY;
    static CursorMode _cursorMode;
};