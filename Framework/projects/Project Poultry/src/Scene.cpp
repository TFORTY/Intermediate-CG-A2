#include "Scene.h"
#include <iostream>
#include <stb_image.h>

using namespace freebird;

Scene::Scene(std::string sceneName, GLFWwindow* wind)
{
	name = sceneName;
	window = wind;
}

void Scene::InitScene()
{
	scene = new entt::registry();

	Entity::SetReg(scene);


	//Set Up Camera
	Entity camEnt = Entity::Create();
	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV
}

void Scene::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

bool Scene::GetComplete()
{
	return levelComplete;
}

void Scene::SetComplete(bool complete)
{
	levelComplete = complete;
}

Entity Scene::GetCamera()
{
	return camEnt;
}

entt::registry* Scene::GetScene()
{
	return scene;
}

Shader::sptr Scene::GetShader()
{
	return shader;
}

bool Scene::GetLoad()
{
	return loadModels;
}

//void Scene::RenderVAO(Shader::sptr& shader, MeshRenderer& vao, Camera& camera, glm::mat4 transform)
//{
//	shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
//	shader->SetUniformMatrix("u_ModelViewProjection", camera.GetViewProjection() * transform);
//	shader->SetUniformMatrix("u_Model", transform);
//	vao.Render();
//}

void Scene::SetShaderValues(Shader::sptr& shader, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 lightCol, float lightAmbientPow, float lightSpecularPow, float lightSpecularPow2, glm::vec3 ambientCol, float ambientPow, float shininess)
{
	shader->SetUniform("u_LightPos", lightPos);
	shader->SetUniform("u_LightDir", lightDir);
	shader->SetUniform("u_LightCol", lightCol);
	shader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shader->SetUniform("u_SpecularLightStrength2", lightSpecularPow2);
	shader->SetUniform("u_AmbientCol", ambientCol);
	shader->SetUniform("u_AmbientStrength", ambientPow);
	shader->SetUniform("u_Shininess", shininess);
}

void Scene::LoadTexImage()
{
		int channels;
		stbi_set_flip_vertically_on_load(true);

		image = stbi_load(fileName, &width, &height, &channels, 0);

		if (image)
			std::cout << "Image loaded: " << width << " x " << height << std::endl;
		else std::cout << "Failed to load image" << std::endl;
}

Entity Scene::GetFBO()
{
	return FBO;
}

Entity Scene::GetGreyscaleEnt()
{
	return greyscaleEnt;
}

std::vector<PostEffect*> Scene::GetEffects()
{
	return effects;
}
