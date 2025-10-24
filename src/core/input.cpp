#include "input.h"

Input* Input::_instance = nullptr;

Input::Input()
{
    if(_instance)
        return;

    _instance = this;

    // Initialize key states
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _currentKeys[i] = false;
        _previousKeys[i] = false;
    }
}

void Input::update(GLFWwindow* window)
{
    // Update key states
    for (int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _previousKeys[i] = _currentKeys[i];
        _currentKeys[i] = glfwGetKey(window, i) == GLFW_PRESS;
    }
}

bool Input::isKeyPressed(int key) const
{
    return _currentKeys[key] && !_previousKeys[key];
}

bool Input::isKeyHeld(int key) const
{
    return _currentKeys[key];
}

Input* Input::get()
{
    return _instance;
}
