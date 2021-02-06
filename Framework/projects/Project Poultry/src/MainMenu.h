#pragma once
#include "Scene.h"
#include <iostream>

using namespace freebird;

class MainMenu : public Scene
{
public:
	
	MainMenu(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:

	/*Entity playButton;
	Entity optionsButton;*/
	Entity backEnt;
	Entity loadEnt;

	Shader::sptr shader;

	Mat /*playMat, optionsMat,*/ backMat, loadMat;

	/*Mesh* play;
	Mesh* options;*/
	Mesh* back;

	/*std::string buttonFile = "Models/UI_Button.obj";*/
	std::string backFile = "Models/Floor.obj";

	GLfloat time = 0.0f;

	bool isLoading = false;
};