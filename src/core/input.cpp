#include "input.h"

bool Input::_currentKeys[GLFW_KEY_LAST];
bool Input::_previousKeys[GLFW_KEY_LAST];
bool Input::_currentMouseButton[GLFW_MOUSE_BUTTON_LAST];
bool Input::_previousMouseButton[GLFW_MOUSE_BUTTON_LAST];

void Input::initialize()
{
    for(int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _currentKeys[i] = false;
        _previousKeys[i] = false;
        
        if(i <= GLFW_MOUSE_BUTTON_LAST)
        {
            _currentMouseButton[i] = false;
            _previousMouseButton[i] = false;
        }
    }
}

void Input::update()
{
    for(int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _previousKeys[i] = _currentKeys[i];
        _currentKeys[i] = glfwGetKey(glfwGetCurrentContext(), i);
        
        if(i <= GLFW_MOUSE_BUTTON_LAST)
        {
            _currentMouseButton[i] = glfwGetMouseButton(glfwGetCurrentContext(), i);
            _previousMouseButton[i] = _currentMouseButton[i];
        }
    }
}