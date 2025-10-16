#include "input.h"

bool Input::_currentKeys[GLFW_KEY_LAST];
bool Input::_previousKeys[GLFW_KEY_LAST];
bool Input::_currentMouseButton[GLFW_MOUSE_BUTTON_LAST];
bool Input::_previousMouseButton[GLFW_MOUSE_BUTTON_LAST];
float Input::_mouseX = 0.0f;
float Input::_mouseY = 0.0f;
CursorMode Input::_cursorMode = CursorMode::NORMAL;

void Input::initialize()
{
    for(int i = 0; i < GLFW_KEY_LAST; i++)
    {
        _currentKeys[i] = false;
        _previousKeys[i] = false;
        
        if(i < GLFW_MOUSE_BUTTON_LAST)
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
        _currentKeys[i] = glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS;
        
        if(i <= GLFW_MOUSE_BUTTON_LAST)
        {
            _previousMouseButton[i] = _currentMouseButton[i];
            _currentMouseButton[i] = glfwGetMouseButton(glfwGetCurrentContext(), i) == GLFW_PRESS;
        }
    }

    double xpos, ypos;
    glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
    _mouseX = static_cast<float>(xpos);
    _mouseY = static_cast<float>(ypos);
}

void Input::setCursorMode(CursorMode mode)
{
    _cursorMode = mode;
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, mode);
}
