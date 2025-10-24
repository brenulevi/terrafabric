#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
    Input();

    void update(GLFWwindow* window);

    bool isKeyPressed(int key) const;
    bool isKeyHeld(int key) const;

    static Input* get();

private:
    bool _currentKeys[GLFW_KEY_LAST];
    bool _previousKeys[GLFW_KEY_LAST];

    static Input* _instance;
};