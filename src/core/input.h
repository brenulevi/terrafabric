#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
    static void initialize();
    static void update();

    inline static bool isKeyHeld(int key) { return _currentKeys[key]; }
    inline static bool isKeyPressed(int key) { return _currentKeys[key] && !_previousKeys[key]; }
    inline static bool isKeyReleased(int key) { return !_currentKeys[key] && _previousKeys[key]; }

private:
    static bool _currentKeys[GLFW_KEY_LAST];
    static bool _previousKeys[GLFW_KEY_LAST];
    static bool _currentMouseButton[GLFW_MOUSE_BUTTON_LAST];
    static bool _previousMouseButton[GLFW_MOUSE_BUTTON_LAST];
};