#pragma once
#include "Scene.h"
#include "Input.h"
#include <vector>
#include <iostream>

class MainMenuLevel : public Scene
{
public:

	MainMenuLevel(std::string sceneName, GLFWwindow* wind);

	void InitScene();

	void Update(float dt);

	void Unload();

private:

	Entity startDoor, optionDoor, exitDoor;
	Entity floorEnt, backWall, leftAngledWall, rightAngledWall, leftWall, rightWall;
	Entity mainPlayer;
	Entity startEnt, optEnt, exitEnt;

	Shader::sptr doorShader, playerShader, floorShader, levelShader;

	Mat drumstickMat, doorMat, floorMat, wallMat;

	std::vector<std::unique_ptr<Mesh>> doorFrames, walkFrames;

	Mesh* drumstick;
	Mesh* floor;
	Mesh* wall;
	Mesh* doorM;
	Mesh* start;
	Mesh* options;
	Mesh* exit;

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
	std::string doorFile = "Models/DoorFrames/Door0.obj";
	std::string floorFile = "Models/Floor.obj";
	std::string wallFile = "Models/Wall.obj";
	std::string startFile = "Models/Start.obj";
	std::string exitFile = "Models/Exit.obj";
	std::string optFile = "Models/Options.obj";

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

	GLfloat time = 0.0f;

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
};
