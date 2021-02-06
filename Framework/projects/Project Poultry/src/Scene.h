#pragma once

#include "Entity.h"
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "Texture2D.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <MeshRenderer.h>
#include <ModelManager.h>

#include "ColorCorrection.h"

using namespace freebird;

class Scene
{

public:
	Scene()
	{
		scene = new entt::registry();
	}
	Scene(std::string sceneName, GLFWwindow* wind);
 

	virtual void InitScene();
	virtual void Update(float dt) {}

	virtual void Unload();

	bool GetComplete();
	void SetComplete(bool complete);

	Entity GetCamera();

	entt::registry* GetScene();
	Shader::sptr GetShader();

	bool GetLoad();

	void SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos = glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3 lightDir = glm::vec3(0.f, 0.f, 0.f), glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f),
		float lightAmbientPow = 0.f, float lightSpecularPow = 0.f, float lightSpecularPow2 = 0.f,
		glm::vec3 ambientCol = glm::vec3(0.f, 0.f, 0.f), float ambientPow = 0.f, float shininess = 0.f);

	struct Mat
	{
		Texture2D::sptr Albedo;
		float Shininess;
	};

	void LoadTexImage();

protected:

	entt::registry* scene = nullptr;
	std::string name = " ";

	Shader::sptr shader, morphShader;

	GLFWwindow* window;

	Entity camEnt, uiCamEnt;

	std::vector<Entity> ents;

	bool levelComplete = false;

	unsigned char* image;
	const char* fileName;
	int width, height;

	bool loadModels = false;
};