#pragma once
#include "Scene.h"
#include "Input.h"
#include "Wire.h"
#include "Lever.h"
#include <vector>
#include <iostream>
#include <ParticleSystem.h>

using namespace freebird;

class Level1 : public Scene
{
public:

	Level1(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:

	Entity mainPlayer;
	Entity floorEnt;
	Entity leftEnt, rightEnt, backEnt;
	Entity andEnt;
	Entity wireEnt, wireEnt2, wireEnt3;
	Entity buttonEnt, buttonEnt2;
	Entity doorEnt;
	Entity coilEnt, coilPowered;
	Entity pipeEnt;
	Entity boxEnt;
	Entity particleEnt;
	Entity wirePowered, wirePowered2, wirePowered3;
	Entity tutEnt;
	Entity completeEnt;

	Shader::sptr playerShader, levelShader, floorShader, gateShader, wireShader, doorShader, buttonShader, particleShader, untexturedShader, uiShader;

	GLfloat time = 0.0f;

	Mat buttonMat, drumstickMat, doorMat, floorMat, wallMat, wireMat, coilMat, gateMat, completeMat;

	std::vector<std::unique_ptr<Mesh>> doorFrames, walkFrames, doorCloseFrames;

	Mesh* drumstick;
	Mesh* floor;
	Mesh* wall;
	Mesh* doorM;
	Mesh* gate;
	Mesh* wireL;
	Mesh* wireR;
	Mesh* wireC;
	Mesh* buttonM;
	Mesh* wireLPower;
	Mesh* wireRPower;
	Mesh* wireCPower;
	Mesh* coil;
	Mesh* coilP;
	Mesh* pipe;
	Mesh* tut;

	Mesh* door1;
	Mesh* door2;
	Mesh* door3;
	Mesh* door4;
	Mesh* door5;
	Mesh* door6;
	Mesh* door7;
	Mesh* door8;
	Mesh* door9;
	Mesh* door10;

	Mesh* walk1;
	Mesh* walk2;
	Mesh* walk3;
	Mesh* walk4;
	Mesh* walk5;
	Mesh* walk6;
	Mesh* walk7;
	Mesh* walk8;
	Mesh* walk9;
	Mesh* walk10;
	Mesh* walk11;
	Mesh* walk12;
	Mesh* walk13;
	Mesh* walk14;

	std::string drumFile = "Models/ChickenFrames/Walk1.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string wallFile = "Models/Wall.obj";
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string gateFile = "Models/AndGate.obj";
	std::string wire1File = "Models/LeftWire.obj";
	std::string wire2File = "Models/RightWire.obj";
	std::string wire3File = "Models/CoilWire.obj";
	std::string buttonFile = "Models/Button.obj";
	std::string coilFile = "Models/Coil.obj";
	std::string pipeFile = "Models/Level1Pipe.obj";
	std::string tutFile = "Models/Interact.obj";


	std::string doorFile1 = "Models/DoorFrames/Door0.obj";
	std::string doorFile2 = "Models/DoorFrames/Door1.obj";
	std::string doorFile3 = "Models/DoorFrames/Door2.obj";
	std::string doorFile4 = "Models/DoorFrames/Door3.obj";
	std::string doorFile5 = "Models/DoorFrames/Door4.obj";
	std::string doorFile6 = "Models/DoorFrames/Door5.obj";
	std::string doorFile7 = "Models/DoorFrames/Door6.obj";
	std::string doorFile8 = "Models/DoorFrames/Door7.obj";
	std::string doorFile9 = "Models/DoorFrames/Door8.obj";
	std::string doorFile10 = "Models/DoorFrames/Door9.obj";

	std::string walkFile1 = "Models/ChickenFrames/Walk1.obj";
	std::string walkFile2 = "Models/ChickenFrames/Walk2.obj";
	std::string walkFile3 = "Models/ChickenFrames/Walk3.obj";
	std::string walkFile4 = "Models/ChickenFrames/Walk4.obj";
	std::string walkFile5 = "Models/ChickenFrames/Walk5.obj";
	std::string walkFile6 = "Models/ChickenFrames/Walk6.obj";
	std::string walkFile7 = "Models/ChickenFrames/Walk7.obj";
	std::string walkFile8 = "Models/ChickenFrames/Walk8.obj";
	std::string walkFile9 = "Models/ChickenFrames/Walk9.obj";
	std::string walkFile10 = "Models/ChickenFrames/Walk10.obj";
	std::string walkFile11 = "Models/ChickenFrames/Walk11.obj";
	std::string walkFile12 = "Models/ChickenFrames/Walk12.obj";
	std::string walkFile13 = "Models/ChickenFrames/Walk13.obj";
	std::string walkFile14 = "Models/ChickenFrames/Walk14.obj";

	ParticleParam particleData;

	float t = 0.0f;
	float totalTime;

	float speed = 4.0f;

	glm::vec3 point1 = glm::vec3(-3.0f, 15.0f, 3.0f);
	glm::vec3 point2 = glm::vec3(3.0f, 15.0f, 3.0f);

	glm::vec3 currentPos = glm::vec3(3.0f, 15.0f, 3.0f);

	bool forwards = true;

	bool camClose = false;
	bool camFar = false;

	int lightNum = 5;

	bool showLevelComplete = false;

	KeyPressWatcher button1Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt.Get<Lever>().SetPowered(!buttonEnt.Get<Lever>().GetPowered());
		std::cout << "Button 1 Power: " << buttonEnt.Get<Lever>().GetPowered() << std::endl;
		});

	KeyPressWatcher button2Watch = KeyPressWatcher(GLFW_KEY_E, [&]() {
		buttonEnt2.Get<Lever>().SetPowered(!buttonEnt2.Get<Lever>().GetPowered());
		std::cout << "Button 2 Power: " << buttonEnt2.Get<Lever>().GetPowered() << std::endl;
		});

};