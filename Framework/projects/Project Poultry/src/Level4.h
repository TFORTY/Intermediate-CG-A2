#pragma once
#include "Scene.h"


using namespace freebird;

class Level4 : public Scene
{
public:

	Level4(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:

	Entity andEnt, andEnt2;

	Shader::sptr shader;

	Mesh* gate;
	Mesh* gate2;


	std::string gateFile = "Models/AndGate.obj";

};