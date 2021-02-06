#include "Level4.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <imgui.h>
#include <AABB.h>
#include <MeshRenderer.h>
#include <MorphRenderer.h>
#include "Texture2DData.h"
#include "Texture2D.h"
#include <stb_image.h>
#include <MorphAnimation.h>

Level4::Level4(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{

	gate = ModelManager::FindMesh(gateFile);
	gate2 = ModelManager::FindMesh(gateFile);

	andEnt = Entity::Create();
}

void Level4::InitScene()
{
	Application::SetClearColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

	shader = Shader::Create();
	shader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	shader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	shader->Link();

	SetShaderValues(shader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(-4.0f, 1.0f, -2.0f));
	gateTrans.SetRotationY(-90.0f);

	auto& gateTrans2 = andEnt2.Add<Transform>();
	gateTrans2.SetPosition(glm::vec3(4.0f, 1.0f, -2.0f));
	gateTrans2.SetRotationY(-90.0f);

	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *gate, shader);
	auto& gateMesh2 = andEnt2.Add<MeshRenderer>(andEnt2, *gate2, shader);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, 10)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

}

void Level4::Update(float dt)
{

	auto& gateTrans = andEnt.Get<Transform>();
	auto& gateTrans2 = andEnt2.Get<Transform>();

	auto& camera = camEnt.Get<Camera>();

	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& gateMesh2 = andEnt2.Get<MeshRenderer>();

	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformGate2 = gateTrans2.GetModelMatrix();

	//CAMERA MOVEMENT
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x - 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x + 10 * dt, camera.GetPosition().y, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y + 10 * dt, camera.GetPosition().z));
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y - 10 * dt, camera.GetPosition().z));
	}

	shader->Bind();
	gateMesh.Render(camera, transformGate);
	gateMesh2.Render(camera, transformGate2);

}

void Level4::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
