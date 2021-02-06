#include "MainMenuLevel.h"
#include <iostream>
#include <GLFW\glfw3.h>

#include "Application.h"
#include <AABB.h>
#include <MeshRenderer.h>
#include <MorphRenderer.h>
#include "Texture2DData.h"
#include "Texture2D.h"
#include <stb_image.h>
#include <MorphAnimation.h>

MainMenuLevel::MainMenuLevel(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
	mainPlayer = Entity::Create();
	startDoor = Entity::Create();
	optionDoor = Entity::Create();
	exitDoor = Entity::Create();
	floorEnt = Entity::Create();
	backWall = Entity::Create();
	leftWall = Entity::Create();
	rightWall = Entity::Create();
	leftAngledWall = Entity::Create();
	rightAngledWall = Entity::Create();
	startEnt = Entity::Create();
	optEnt = Entity::Create();
	exitEnt = Entity::Create();
	FBO = Entity::Create();
	greyscaleEnt = Entity::Create();

	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	wall = ModelManager::FindMesh(wallFile);
	doorM = ModelManager::FindMesh(doorFile);
	start = ModelManager::FindMesh(startFile, glm::vec3(1.0f, 0.0f, 0.0f));
	exit = ModelManager::FindMesh(exitFile, glm::vec3(1.0f, 0.0f, 0.0f));
	options = ModelManager::FindMesh(optFile, glm::vec3(1.0f, 0.0f, 0.0f));

	door1 = ModelManager::FindMesh(doorFile1);
	door2 = ModelManager::FindMesh(doorFile2);
	door3 = ModelManager::FindMesh(doorFile3);
	door4 = ModelManager::FindMesh(doorFile4);
	door5 = ModelManager::FindMesh(doorFile5);
	door6 = ModelManager::FindMesh(doorFile6);
	door7 = ModelManager::FindMesh(doorFile7);
	door8 = ModelManager::FindMesh(doorFile8);
	door9 = ModelManager::FindMesh(doorFile9);
	door10 = ModelManager::FindMesh(doorFile10);

	walk1 = ModelManager::FindMesh(walkFile1);
	walk2 = ModelManager::FindMesh(walkFile2);
	walk3 = ModelManager::FindMesh(walkFile3);
	walk4 = ModelManager::FindMesh(walkFile4);
	walk5 = ModelManager::FindMesh(walkFile5);
	walk6 = ModelManager::FindMesh(walkFile6);
	walk7 = ModelManager::FindMesh(walkFile7);
	walk8 = ModelManager::FindMesh(walkFile8);
	walk9 = ModelManager::FindMesh(walkFile9);
	walk10 = ModelManager::FindMesh(walkFile10);
	walk11 = ModelManager::FindMesh(walkFile11);
	walk12 = ModelManager::FindMesh(walkFile12);
	walk13 = ModelManager::FindMesh(walkFile13);
	walk14 = ModelManager::FindMesh(walkFile14);
}

void MainMenuLevel::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

	effects.clear();

#pragma region Shader Stuff

	glm::vec3 lightPos = glm::vec3(0.0f, 9.5f, -35.0f);
	glm::vec3 lightDir = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.f, 1.f, 1.f);
	float     lightAmbientPow = 0.05f;
	float     lightSpecularPow = 1.0f;
	float     lightSpecularPow2 = 0.2f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
	float     shininess = 16.0f;

	playerShader = Shader::Create();
	playerShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	playerShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	playerShader->Link();

	SetShaderValues(playerShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	doorShader = Shader::Create();
	doorShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	doorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	doorShader->Link();

	SetShaderValues(doorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	floorShader = Shader::Create();
	floorShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	floorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	floorShader->Link();

	SetShaderValues(floorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	levelShader = Shader::Create();
	levelShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	levelShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	levelShader->Link();

	SetShaderValues(levelShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);
#pragma endregion

#pragma region Texture Stuff
	Texture2DData::sptr drumstickMap = Texture2DData::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2DData::sptr doorMap = Texture2DData::LoadFromFile("Textures/DoorTexture.png");
	Texture2DData::sptr floorMap = Texture2DData::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2DData::sptr wallMap = Texture2DData::LoadFromFile("Textures/WallTexture.jpg");

	Texture2D::sptr diffuseDrum = Texture2D::Create();
	diffuseDrum->LoadData(drumstickMap);

	Texture2D::sptr diffuseDoor = Texture2D::Create();
	diffuseDoor->LoadData(doorMap);

	Texture2D::sptr diffuseFloor = Texture2D::Create();
	diffuseFloor->LoadData(floorMap);

	Texture2D::sptr diffuseWall = Texture2D::Create();
	diffuseWall->LoadData(wallMap);

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	drumstickMat.Albedo = diffuseDrum;
	doorMat.Albedo = diffuseDoor;
	floorMat.Albedo = diffuseFloor;
	wallMat.Albedo = diffuseWall;
#pragma endregion

	//TRANSFORMS
	auto& floorTrans = floorEnt.Add<Transform>();
	floorTrans.SetScale(glm::vec3(2.0f));

	auto& leftTrans = leftWall.Add<Transform>();
	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);
	leftTrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& leftATrans = leftAngledWall.Add<Transform>();
	leftATrans.SetRotationY(45.0f);
	leftATrans.SetPositionX(-45.0f);
	leftATrans.SetPositionZ(-10.0f);
	leftATrans.SetPositionY(9.0f);
	leftATrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& rightATrans = rightAngledWall.Add<Transform>();
	rightATrans.SetRotationY(-45.0f);
	rightATrans.SetPositionX(45.0f);
	rightATrans.SetPositionZ(-10.0f);
	rightATrans.SetPositionY(9.0f);
	rightATrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& rightTrans = rightWall.Add<Transform>();
	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);
	rightTrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& backTrans = backWall.Add<Transform>();
	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);
	backTrans.SetScale(glm::vec3(1.0f, 5.0f, 1.0f));

	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	playerTrans.SetRotationY(0.0f);

	auto& startTrans = startDoor.Add<Transform>();
	startTrans.SetPosition(glm::vec3(0.0f, -1.0f, -38.0f));
	startTrans.SetScale(glm::vec3(1.5f));

	auto& optTrans = optionDoor.Add<Transform>();
	optTrans.SetPosition(glm::vec3(-30.0f, -1.0f, -27.5f));
	optTrans.SetScale(glm::vec3(1.5f));
	optTrans.SetRotationY(45.0f);
	
	auto& exitTrans = exitDoor.Add<Transform>();
	exitTrans.SetPosition(glm::vec3(30.0f, -1.0f, -27.5f));
	exitTrans.SetScale(glm::vec3(1.5f));
	exitTrans.SetRotationY(-45.0f);

	auto& sTrans = startEnt.Add<Transform>();
	sTrans.SetPosition(glm::vec3(-4.0f, 2.5f, -25.0f));
	sTrans.SetScale(glm::vec3(4.0f));

	auto& eTrans = exitEnt.Add<Transform>();
	eTrans.SetRotationY(-45.0f);
	eTrans.SetPosition(glm::vec3(19.0f, 2.5f, -21.0f));
	eTrans.SetScale(glm::vec3(4.0f));

	auto& oTrans = optEnt.Add<Transform>();
	oTrans.SetRotationY(45.0f);
	oTrans.SetPosition(glm::vec3(-26.0f, 2.5f, -13.0f));
	oTrans.SetScale(glm::vec3(4.0f));
	
	//DOORS
	auto& doorS = startDoor.Add<Door>();
	doorS.SetOpen(true);
	auto& doorO = optionDoor.Add<Door>();
	doorO.SetOpen(true);
	auto& doorE = exitDoor.Add<Door>();
	doorE.SetOpen(true);

	//AABB
	auto& leftCol = leftWall.Add<AABB>(leftWall, mainPlayer);
	auto& leftACol = leftAngledWall.Add<AABB>(leftAngledWall, mainPlayer);
	auto& rightCol = rightWall.Add<AABB>(rightWall, mainPlayer);
	auto& rightACol = rightAngledWall.Add<AABB>(rightAngledWall, mainPlayer);
	auto& backCol = backWall.Add<AABB>(backWall, mainPlayer);
	auto& startCol = startDoor.Add<AABB>(startDoor, mainPlayer);
	//startCol.SetComplete(false);
	auto& optCol = optionDoor.Add<AABB>(optionDoor, mainPlayer);
	//optCol.SetComplete(false);
	auto& exitCol = exitDoor.Add<AABB>(exitDoor, mainPlayer);
	//exitCol.SetComplete(false);

	doorFrames.push_back(std::unique_ptr<Mesh>(door1));
	doorFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorFrames.push_back(std::unique_ptr<Mesh>(door4));
	doorFrames.push_back(std::unique_ptr<Mesh>(door5));
	doorFrames.push_back(std::unique_ptr<Mesh>(door6));
	doorFrames.push_back(std::unique_ptr<Mesh>(door7));
	doorFrames.push_back(std::unique_ptr<Mesh>(door8));
	doorFrames.push_back(std::unique_ptr<Mesh>(door9));
	doorFrames.push_back(std::unique_ptr<Mesh>(door10));


	walkFrames.push_back(std::unique_ptr<Mesh>(walk1));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk2));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk3));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk4));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk5));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk6));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk7));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk8));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk9));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk10));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk11));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk12));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk13));
	walkFrames.push_back(std::unique_ptr<Mesh>(walk14));

	auto& playerMesh = mainPlayer.Add<MorphRenderer>(mainPlayer, *drumstick, playerShader);
	auto& backMesh = backWall.Add<MeshRenderer>(backWall, *wall, levelShader);
	auto& leftMesh = leftWall.Add<MeshRenderer>(leftWall, *wall, levelShader);
	auto& rightMesh = rightWall.Add<MeshRenderer>(rightWall, *wall, levelShader);
	auto& leftAMesh = leftAngledWall.Add<MeshRenderer>(leftAngledWall, *wall, levelShader);
	auto& rightAMesh = rightAngledWall.Add<MeshRenderer>(rightAngledWall, *wall, levelShader);
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, floorShader);
	auto& playMesh = startDoor.Add<MorphRenderer>(startDoor, *doorM, doorShader);
	auto& exitMesh = exitDoor.Add<MorphRenderer>(exitDoor, *doorM, doorShader);
	auto& optMesh = optionDoor.Add<MorphRenderer>(optionDoor, *doorM, doorShader);
	auto& sMesh = startEnt.Add<MeshRenderer>(startEnt, *start, levelShader);
	auto& oMesh = optEnt.Add<MeshRenderer>(optEnt, *options, levelShader);
	auto& eMesh = exitEnt.Add<MeshRenderer>(exitEnt, *exit, levelShader);

	auto& startAnimator = startDoor.Add<MorphAnimation>(startDoor);
	startAnimator.SetTime(0.2f);
	startAnimator.SetFrames(doorFrames);
	startAnimator.SetLoop(false);

	auto& exitAnimator = exitDoor.Add<MorphAnimation>(exitDoor);
	exitAnimator.SetTime(0.2f);
	exitAnimator.SetFrames(doorFrames);
	exitAnimator.SetLoop(false);

	auto& optAnimator = optionDoor.Add<MorphAnimation>(optionDoor);
	optAnimator.SetTime(0.2f);
	optAnimator.SetFrames(doorFrames);
	optAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.05f);
	walkAnimator.SetFrames(walkFrames);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 25, 15)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV


	int width, height;
	glfwGetWindowSize(window, &width, &height);

	auto basicEffect = &FBO.Add<PostEffect>();
	basicEffect->Init(width, height);

	auto greyscaleEffect = &greyscaleEnt.Add<Greyscale>();
	greyscaleEffect->Init(width, height);

	effects.push_back(greyscaleEffect);
}

void MainMenuLevel::Update(float dt)
{

	time += dt;
	playerShader->SetUniform("u_Time", time);
	levelShader->SetUniform("u_Time", time);
	doorShader->SetUniform("u_Time", time);
	floorShader->SetUniform("u_Time", time);

	if (forwards)
		t += dt / totalTime;
	else
		t -= dt / totalTime;

	if (t < 0.0f)
		t = 0.0f;

	if (t > 1.0f)
		t = 1.0f;

	if (t >= 1.0f || t <= 0.0f)
		forwards = !forwards;

	currentPos = glm::mix(point1, point2, t);

	playerShader->SetUniform("u_Position", currentPos);
	levelShader->SetUniform("u_Position", currentPos);
	floorShader->SetUniform("u_Position", currentPos);
	doorShader->SetUniform("u_Position", currentPos);

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftWall.Get<Transform>();
	auto& leftATrans = leftAngledWall.Get<Transform>();
	auto& rightATrans = rightAngledWall.Get<Transform>();
	auto& rightTrans = rightWall.Get<Transform>();
	auto& backTrans = backWall.Get<Transform>();
	auto& startTrans = startDoor.Get<Transform>();
	auto& exitTrans = exitDoor.Get<Transform>();
	auto& optTrans = optionDoor.Get<Transform>();
	auto& sTrans = startEnt.Get<Transform>();
	auto& oTrans = optEnt.Get<Transform>();
	auto& eTrans = exitEnt.Get<Transform>();

	auto& camera = camEnt.Get<Camera>();

	camera.LookAt(glm::vec3(playerTrans.GetPosition()));

	auto& drumMesh = mainPlayer.Get<MorphRenderer>();
	auto& floorMesh = floorEnt.Get<MeshRenderer>();
	auto& backMesh = backWall.Get<MeshRenderer>();
	auto& leftMesh = leftWall.Get<MeshRenderer>();
	auto& rightMesh = rightWall.Get<MeshRenderer>();
	auto& leftAMesh = leftAngledWall.Get<MeshRenderer>();
	auto& rightAMesh = rightAngledWall.Get<MeshRenderer>();
	auto& startMesh = startDoor.Get<MorphRenderer>();
	auto& exitMesh = exitDoor.Get<MorphRenderer>();
	auto& optMesh = optionDoor.Get<MorphRenderer>();
	auto& sMesh = startEnt.Get<MeshRenderer>();
	auto& oMesh = optEnt.Get<MeshRenderer>();
	auto& eMesh = exitEnt.Get<MeshRenderer>();

	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformFloor = groundTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformLeftA = leftATrans.GetModelMatrix();
	glm::mat4 transformRightA = rightATrans.GetModelMatrix();
	glm::mat4 transformStart = startTrans.GetModelMatrix();
	glm::mat4 transformExit = exitTrans.GetModelMatrix();
	glm::mat4 transformOpt = optTrans.GetModelMatrix();
	glm::mat4 transformS = sTrans.GetModelMatrix();
	glm::mat4 transformO = oTrans.GetModelMatrix();
	glm::mat4 transformE = eTrans.GetModelMatrix();

#pragma region PlayerMovement
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(225.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camFar)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(315.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camClose)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(45.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camClose)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		playerTrans.SetRotationY(135.0f);

		playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
		playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);

		camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

		if (camFar)
			camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

		mainPlayer.Get<MorphAnimation>().Update(dt);
	}

	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveLeft())
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() - 10 * dt);
			playerTrans.SetRotationY(270.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveRight())
		{
			playerTrans.SetPositionX(playerTrans.GetPositionX() + 10 * dt);
			playerTrans.SetRotationY(90.0f);
			camera.SetPosition(glm::vec3(playerTrans.GetPositionX(), camera.GetPosition().y, camera.GetPosition().z));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveUp())
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() - 10 * dt);
			playerTrans.SetRotationY(180.0f);

			if (camFar)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z - 10 * dt));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		if (playerTrans.GetCanMoveDown())
		{
			playerTrans.SetPositionZ(playerTrans.GetPositionZ() + 10 * dt);
			playerTrans.SetRotationY(0.0f);

			if (camClose)
				camera.SetPosition(glm::vec3(camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z + 10 * dt));

			mainPlayer.Get<MorphAnimation>().Update(dt);
		}
	}
#pragma endregion

#pragma region CameraMovement

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
#pragma endregion

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		lightNum = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		lightNum = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		lightNum = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		lightNum = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		lightNum = 5;
	}


	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	playerShader->SetUniform("u_LightNum", lightNum);
	doorShader->SetUniform("u_LightNum", lightNum);
	floorShader->SetUniform("u_LightNum", lightNum);
	levelShader->SetUniform("u_LightNum", lightNum);

	auto basicEffect = &FBO.Get<PostEffect>();
	auto greyscaleEffect = &greyscaleEnt.Get<Greyscale>();

	basicEffect->Clear();
	greyscaleEffect->Clear();


	basicEffect->BindBuffer(0);

#pragma region Renders
		playerShader->Bind();
		playerShader->SetUniform("s_Diffuse", 0);
		drumstickMat.Albedo->Bind(0);
		drumMesh.Render(camera, transform);

		levelShader->Bind();
		levelShader->SetUniform("s_Diffuse", 0);
		wallMat.Albedo->Bind(0);
		leftMesh.Render(camera, transformLeft);
		rightMesh.Render(camera, transformRight);
		backMesh.Render(camera, transformBack);
		leftAMesh.Render(camera, transformLeftA);
		rightAMesh.Render(camera, transformRightA);
		sMesh.Render(camera, transformS);
		oMesh.Render(camera, transformO);
		eMesh.Render(camera, transformE);

		floorShader->Bind();
		floorShader->SetUniform("s_Diffuse", 0);
		floorMat.Albedo->Bind(0);
		floorMesh.Render(camera, transformFloor);

		doorShader->Bind();
		doorShader->SetUniform("s_Diffuse", 0);
		doorMat.Albedo->Bind(0);
		startMesh.Render(camera, transformStart);
		exitMesh.Render(camera, transformExit);
		optMesh.Render(camera, transformOpt);
		doorMat.Albedo->Unbind(0);	
#pragma endregion

	basicEffect->UnbindBuffer();

	greyscaleEffect->ApplyEffect(basicEffect);

	greyscaleEffect->DrawToScreen();

	startDoor.Get<AABB>().Update();
	optionDoor.Get<AABB>().Update();
	exitDoor.Get<AABB>().Update();
	leftWall.Get<AABB>().Update();
	rightWall.Get<AABB>().Update();
	backWall.Get<AABB>().Update();
	leftAngledWall.Get<AABB>().Update();
	rightAngledWall.Get<AABB>().Update();

	if (startDoor.Get<Door>().GetOpen())
		startDoor.Get<MorphAnimation>().Update(dt);

	if (exitDoor.Get<Door>().GetOpen())
		exitDoor.Get<MorphAnimation>().Update(dt);

	if (optionDoor.Get<Door>().GetOpen())
		optionDoor.Get<MorphAnimation>().Update(dt);

	if (startDoor.Get<AABB>().GetComplete())
		levelComplete = true;

	if (exitDoor.Get<AABB>().GetComplete())
		glfwSetWindowShouldClose(window, true);

}

void MainMenuLevel::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}
