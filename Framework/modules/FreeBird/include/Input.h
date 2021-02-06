#pragma once

#include <functional>
#include <Entity.h>

struct GLFWwindow;

namespace freebird
{
	struct KeyPressWatcher final
	{
	public:
		KeyPressWatcher(int keyCode, const std::function<void()>& onPressed);
		~KeyPressWatcher() = default;

		bool Poll(GLFWwindow* window) const;

	protected:
		int _keyCode;
		mutable bool _isPressed;
		std::function<void()> _onPressed;
	};


	class Input
	{
	public:




	private:
	};
}