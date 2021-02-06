#pragma once
#include <Logging.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <wtypes.h>

#include <filesystem>
#include <fstream>

//ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//Referenced in conjunction with NOU and Shawn's setup of a window from the CG Tutorials//

namespace freebird
{
	class Application
	{
	public:
		~Application() = default;

		//Inits a window
		//static void Init(const std::string name, int w, int h);
		static GLFWwindow* Init(std::string name, int w, int h);

		//Sets the clear color of the window
		static void SetClearColor(const glm::vec4& color);

		static void Update();
		static void SwapBuffers();
		static void ProcessInput(GLFWwindow* window);

		static void Cleanup();

		static float GetDT();
		static void Tick();
		
		static bool IsClosing();

		//ImGui
		static void InitImGui();
		static void ShutdownImGui();
		static void RenderImGui();

		static std::vector<std::function<void()>> imGuiCallbacks;

	protected:
		Application() = default;
		static GLFWwindow* m_window;
		static float m_dt;
		static float m_thisFrame;
	};
}