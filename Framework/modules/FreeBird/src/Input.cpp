#include "Input.h"
#include <GLFW/glfw3.h>
#include <Lever.h>
#include <iostream>

namespace freebird
{
	KeyPressWatcher::KeyPressWatcher(int keyCode, const std::function<void()>& onPressed)
	{
		_isPressed = false;
		_keyCode = keyCode;
		_onPressed = onPressed;
		
	}
	bool KeyPressWatcher::Poll(GLFWwindow* window) const
	{
		if (glfwGetKey(window, _keyCode) == GLFW_PRESS) {
			if (!_isPressed) {
				_isPressed = true;
				if (_onPressed) {
					_onPressed();
				}
			}
			return false;
		}
		else {
			_isPressed = false;
		}
		return false;
	}
}