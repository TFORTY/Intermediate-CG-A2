#include "Level1.h"
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

using namespace freebird;

Level1::Level1(std::string sceneName, GLFWwindow* wind)
	: Scene(sceneName, wind)
{
	mainPlayer = Entity::Create();
	floorEnt = Entity::Create();
	leftEnt = Entity::Create();
	rightEnt = Entity::Create();
	backEnt = Entity::Create();
	buttonEnt = Entity::Create();
	buttonEnt2 = Entity::Create();
	wireEnt = Entity::Create();
	wireEnt2 = Entity::Create();
	wireEnt3 = Entity::Create();
	andEnt = Entity::Create();
	doorEnt = Entity::Create();
	coilEnt = Entity::Create();
	coilPowered = Entity::Create();
	pipeEnt = Entity::Create();
	boxEnt = Entity::Create();
	particleEnt = Entity::Create();
	wirePowered = Entity::Create();
	wirePowered2 = Entity::Create();
	wirePowered3 = Entity::Create();
	completeEnt = Entity::Create();
	tutEnt = Entity::Create();

	drumstick = ModelManager::FindMesh(drumFile);
	floor = ModelManager::FindMesh(floorFile);
	wall = ModelManager::FindMesh(wallFile);
	doorM = ModelManager::FindMesh(doorFile);
	buttonM = ModelManager::FindMesh(buttonFile);
	wireL = ModelManager::FindMesh(wire1File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireR = ModelManager::FindMesh(wire2File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireC = ModelManager::FindMesh(wire3File, glm::vec3(1.0f, 0.0f, 0.0f));
	wireLPower = ModelManager::FindMesh(wire1File, glm::vec3(0.0f, 1.0f, 0.0f));
	wireRPower = ModelManager::FindMesh(wire2File, glm::vec3(0.0f, 1.0f, 0.0f));
	wireCPower = ModelManager::FindMesh(wire3File, glm::vec3(0.0f, 1.0f, 0.0f));
	gate = ModelManager::FindMesh(gateFile, glm::vec3(0.0f, 0.0f, 1.0f));
	coil = ModelManager::FindMesh(coilFile, glm::vec3(1.0f, 0.0f, 0.0f));
	coilP = ModelManager::FindMesh(coilFile, glm::vec3(0.0f, 1.0f, 0.0f));
	pipe = ModelManager::FindMesh(pipeFile, glm::vec3(0.6f, 0.45f, 0.0f));
	tut = ModelManager::FindMesh(tutFile, glm::vec3(1.0f, 0.0f, 0.0f));

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

void Level1::InitScene()
{
	Application::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	scene = new entt::registry();

	Entity::SetReg(scene);

	float distance = glm::distance(point2, point1);

	totalTime = distance / speed;

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

	levelShader = Shader::Create();
	levelShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	levelShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	levelShader->Link();

	SetShaderValues(levelShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	floorShader = Shader::Create();
	floorShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	floorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	floorShader->Link();

	SetShaderValues(floorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	wireShader = Shader::Create();
	wireShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	wireShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	wireShader->Link();

	SetShaderValues(wireShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	gateShader = Shader::Create();
	gateShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	gateShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	gateShader->Link();

	SetShaderValues(gateShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	buttonShader = Shader::Create();
	buttonShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	buttonShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	buttonShader->Link();

	SetShaderValues(buttonShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	doorShader = Shader::Create();
	doorShader->LoadShaderPartFromFile("Shaders/morph_shader.glsl", GL_VERTEX_SHADER);
	doorShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	doorShader->Link();

	SetShaderValues(doorShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	particleShader = Shader::Create();
	particleShader->LoadShaderPartFromFile("Shaders/particle_vertex.glsl", GL_VERTEX_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_geom.glsl", GL_GEOMETRY_SHADER);
	particleShader->LoadShaderPartFromFile("Shaders/particle_frag.glsl", GL_FRAGMENT_SHADER);
	particleShader->Link();

	untexturedShader = Shader::Create();
	untexturedShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	untexturedShader->LoadShaderPartFromFile("Shaders/frag_untextured.glsl", GL_FRAGMENT_SHADER);
	untexturedShader->Link();

	SetShaderValues(untexturedShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);

	/*uiShader = Shader::Create();
	uiShader->LoadShaderPartFromFile("Shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	uiShader->LoadShaderPartFromFile("Shaders/frag_shader.glsl", GL_FRAGMENT_SHADER);
	uiShader->Link();

	SetShaderValues(uiShader, lightPos, lightDir, lightCol, lightAmbientPow, lightSpecularPow, lightSpecularPow2, ambientCol, ambientPow, shininess);*/

#pragma endregion

#pragma region Texture Stuff
	Texture2DData::sptr buttonMap = Texture2DData::LoadFromFile("Textures/ButtonTexture.png");
	Texture2DData::sptr drumstickMap = Texture2DData::LoadFromFile("Textures/DrumstickTexture.png");
	Texture2DData::sptr doorMap = Texture2DData::LoadFromFile("Textures/DoorTexture.png");
	Texture2DData::sptr floorMap = Texture2DData::LoadFromFile("Textures/FloorTexture.jpg");
	Texture2DData::sptr wallMap = Texture2DData::LoadFromFile("Textures/WallTexture.jpg");
	Texture2DData::sptr wireMap = Texture2DData::LoadFromFile("Textures/WireTexture.png");
	Texture2DData::sptr uiMap = Texture2DData::LoadFromFile("Textures/Buttons/Default/Option.png");
	Texture2DData::sptr completeMap = Texture2DData::LoadFromFile("Textures/LevelComplete.png");

	Texture2D::sptr diffuseButton = Texture2D::Create();
	diffuseButton->LoadData(buttonMap);

	Texture2D::sptr diffuseDrum = Texture2D::Create();
	diffuseDrum->LoadData(drumstickMap);

	Texture2D::sptr diffuseDoor = Texture2D::Create();
	diffuseDoor->LoadData(doorMap);

	Texture2D::sptr diffuseFloor = Texture2D::Create();
	diffuseFloor->LoadData(floorMap);

	Texture2D::sptr diffuseWall = Texture2D::Create();
	diffuseWall->LoadData(wallMap);

	Texture2D::sptr diffuseWire = Texture2D::Create();
	diffuseWire->LoadData(wireMap);

	Texture2D::sptr diffuseUI = Texture2D::Create();
	diffuseUI->LoadData(uiMap);

	Texture2D::sptr diffuseComplete = Texture2D::Create();
	diffuseComplete->LoadData(completeMap);

	Texture2DDescription desc = Texture2DDescription();
	desc.Width = 1;
	desc.Height = 1;
	desc.Format = InternalFormat::RGB8;
	Texture2D::sptr texture2 = Texture2D::Create(desc);
	texture2->Clear();

	buttonMat.Albedo = diffuseButton;
	drumstickMat.Albedo = diffuseDrum;
	doorMat.Albedo = diffuseDoor;
	floorMat.Albedo = diffuseFloor;
	wallMat.Albedo = diffuseWall;
	wireMat.Albedo = diffuseWire;
	completeMat.Albedo = diffuseComplete;

#pragma endregion


	//Transforms
	auto& particleTrans = particleEnt.Add<Transform>();
	particleTrans.SetPosition(glm::vec3(0.0f, 4.0f, -2.0f));

	auto& playerTrans = mainPlayer.Add<Transform>();
	playerTrans.SetPosition(glm::vec3(0.0f, 1.0f, 30.0f));
	playerTrans.SetRotationY(0.0f);

	/*auto& uiTrans = UIEnt.Add<Transform>();
	uiTrans.SetPosition(glm::vec3(8.0f, 8.0f, 0.0f));
	uiTrans.SetRotationY(50.0f);*/

	auto& tutTrans = tutEnt.Add<Transform>();
	tutTrans.SetPosition(glm::vec3(-8.0f, 1.0f, 15.0f));
	tutTrans.SetScale(glm::vec3(3.0f));

	auto& groundTrans = floorEnt.Add<Transform>();

	auto& leftTrans = leftEnt.Add<Transform>();

	auto& rightTrans = rightEnt.Add<Transform>();

	auto& backTrans = backEnt.Add<Transform>();

	auto& wireTrans = wireEnt.Add<Transform>();
	wireTrans.SetPosition(glm::vec3(-6.4f, 2.0f, 1.5f));

	auto& wireTrans2 = wireEnt2.Add<Transform>();
	wireTrans2.SetPosition(glm::vec3(22.0f, 2.0f, 5.0f));

	auto& wireTrans3 = wireEnt3.Add<Transform>();
	wireTrans3.SetPosition(glm::vec3(-16.2f, 2.0f, -10.5));

	auto& buttonTrans = buttonEnt.Add<Transform>();
	buttonTrans.SetPosition(glm::vec3(-22.0f, -2.0f, 21.0f));
	buttonTrans.SetRotationY(90.0f);

	auto& buttonTrans2 = buttonEnt2.Add<Transform>();
	buttonTrans2.SetPosition(glm::vec3(22.0f, -2.0f, 21.0f));
	buttonTrans2.SetRotationY(90.0f);

	auto& doorTrans = doorEnt.Add<Transform>();
	doorTrans.SetPosition(glm::vec3(0.0f, -1.0f, -36.0f));
	doorTrans.SetScale(glm::vec3(1.5f));

	auto& pipeTrans = pipeEnt.Add<Transform>();
	pipeTrans.SetPositionX(-35.5f);
	pipeTrans.SetPositionY(10.5f);

	auto& gateTrans = andEnt.Add<Transform>();
	gateTrans.SetPosition(glm::vec3(0.0f, 1.0f, -2.0f));
	gateTrans.SetRotationY(-90.0f);

	auto& coilTrans = coilEnt.Add<Transform>();
	coilTrans.SetPosition(glm::vec3(-15.0f, 2.0f, -36.0f));
	coilTrans.SetRotationY(180.0f);

	auto& completeTrans = completeEnt.Add<Transform>();
	completeTrans.SetPosition(glm::vec3(0.0f, 1.0f, 0.0f));
	completeTrans.SetScale(glm::vec3(0.22f));


	//AABB
	auto& leftCol = leftEnt.Add<AABB>(leftEnt, mainPlayer);
	auto& rightCol = rightEnt.Add<AABB>(rightEnt, mainPlayer);
	auto& backCol = backEnt.Add<AABB>(backEnt, mainPlayer);
	auto& gateCol = andEnt.Add<AABB>(andEnt, mainPlayer);
	auto& coilCol = coilEnt.Add<AABB>(coilEnt, mainPlayer);
	auto& doorCol = doorEnt.Add<AABB>(doorEnt, mainPlayer);
	doorCol.SetComplete(false);

	//Buttons
	auto& button = buttonEnt.Add<Lever>(wireEnt);
	button.SetPowered(false);
	auto& button2 = buttonEnt2.Add<Lever>(wireEnt2);
	button2.SetPowered(false);

	//Wires
	auto& wire = wireEnt.Add<Wire>(buttonEnt);
	auto& wire2 = wireEnt2.Add<Wire>(buttonEnt2);
	auto& wire3 = wireEnt3.Add<Wire>(andEnt);

	//Gates
	auto& andGate = andEnt.Add<AndGate>(wireEnt, wireEnt2, doorEnt);

	//Door
	auto& door = doorEnt.Add<Door>();
	door.SetOpen(false);

	//Particle
	auto& particleSystem = particleEnt.Add<ParticleSystem>(particleEnt, particleData);

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

	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door10));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door9));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door8));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door7));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door6));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door5));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door4));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door3));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door2));
	doorCloseFrames.push_back(std::unique_ptr<Mesh>(door1));


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
	auto& floorMesh = floorEnt.Add<MeshRenderer>(floorEnt, *floor, floorShader);
	auto& leftMesh = leftEnt.Add<MeshRenderer>(leftEnt, *wall, levelShader);
	auto& rightMesh = rightEnt.Add<MeshRenderer>(rightEnt, *wall, levelShader);
	auto& backMesh = backEnt.Add<MeshRenderer>(backEnt, *wall, levelShader);
	auto& gateMesh = andEnt.Add<MeshRenderer>(andEnt, *gate, untexturedShader);
	auto& buttonMesh = buttonEnt.Add<MeshRenderer>(buttonEnt, *buttonM, buttonShader);
	auto& buttonMesh2 = buttonEnt2.Add<MeshRenderer>(buttonEnt2, *buttonM, buttonShader);
	auto& wireMesh = wireEnt.Add<MeshRenderer>(wireEnt, *wireL, wireShader);
	auto& wireMesh2 = wireEnt2.Add<MeshRenderer>(wireEnt2, *wireR, wireShader);
	auto& wireMesh3 = wireEnt3.Add<MeshRenderer>(wireEnt3, *wireC, wireShader);
	auto& wireMeshP = wirePowered.Add<MeshRenderer>(wirePowered, *wireLPower, wireShader);
	auto& wireMeshP2 = wirePowered2.Add<MeshRenderer>(wirePowered2, *wireRPower, wireShader);
	auto& wireMeshP3 = wirePowered3.Add<MeshRenderer>(wirePowered3, *wireCPower, wireShader);
	auto& doorMesh = doorEnt.Add<MorphRenderer>(doorEnt, *doorM, doorShader);
	auto& pipeMesh = pipeEnt.Add<MeshRenderer>(pipeEnt, *pipe, untexturedShader);
	auto& coilMesh = coilEnt.Add<MeshRenderer>(coilEnt, *coil, untexturedShader);
	auto& coilMeshP = coilPowered.Add<MeshRenderer>(coilPowered, *coilP, untexturedShader);
	auto& tutMesh = tutEnt.Add<MeshRenderer>(tutEnt, *tut, untexturedShader);
	auto& completeMesh = completeEnt.Add<MeshRenderer>(completeEnt, *floor, levelShader);

	auto& doorAnimator = doorEnt.Add<MorphAnimation>(doorEnt);
	doorAnimator.SetTime(0.2f);
	doorAnimator.SetFrames(doorFrames);
	doorAnimator.SetLoop(false);

	auto& walkAnimator = mainPlayer.Add<MorphAnimation>(mainPlayer);
	walkAnimator.SetTime(0.05f);
	walkAnimator.SetFrames(walkFrames);

	auto& camera = camEnt.Add<Camera>();

	camera.SetPosition(glm::vec3(0, 15, mainPlayer.Get<Transform>().GetPositionZ() + 12)); // Set initial position
	camera.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	camera.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camera.SetFovDegrees(90.0f); // Set an initial FOV

	auto& orthoCam = uiCamEnt.Add<Camera>();
	orthoCam.SetPosition(glm::vec3(0, 10, 0)); // Set initial position
	orthoCam.SetUp(glm::vec3(0, 0, -1)); // Use a z-up coordinate system
	orthoCam.LookAt(glm::vec3(0.0f)); // Look at center of the screen
	orthoCam.SetFovDegrees(90.0f); // Set an initial FOV
}

void Level1::Update(float dt)
{

	time += dt;
	playerShader->SetUniform("u_Time", time);
	levelShader->SetUniform("u_Time", time);
	floorShader->SetUniform("u_Time", time);
	gateShader->SetUniform("u_Time", time);
	wireShader->SetUniform("u_Time", time);
	buttonShader->SetUniform("u_Time", time);
	doorShader->SetUniform("u_Time", time);
	untexturedShader->SetUniform("u_Time", time);

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
	gateShader->SetUniform("u_Position", currentPos);
	wireShader->SetUniform("u_Position", currentPos);
	doorShader->SetUniform("u_Position", currentPos);
	buttonShader->SetUniform("u_Position", currentPos);
	untexturedShader->SetUniform("u_Position", currentPos);

	if (doorEnt.Get<Door>().GetOpen())
		doorEnt.Get<MorphAnimation>().SetFrames(doorFrames);
	else
		doorEnt.Get<MorphAnimation>().SetFrames(doorCloseFrames);

	//Transforms
	auto& playerTrans = mainPlayer.Get<Transform>();
	auto& groundTrans = floorEnt.Get<Transform>();
	auto& leftTrans = leftEnt.Get<Transform>();
	auto& rightTrans = rightEnt.Get<Transform>();
	auto& backTrans = backEnt.Get<Transform>();
	auto& doorTrans = doorEnt.Get<Transform>();
	auto& pipeTrans = pipeEnt.Get<Transform>();
	auto& buttonTrans = buttonEnt.Get<Transform>();
	auto& buttonTrans2 = buttonEnt2.Get<Transform>();
	auto& wireTrans = wireEnt.Get<Transform>();
	auto& wireTrans2 = wireEnt2.Get<Transform>();
	auto& wireTrans3 = wireEnt3.Get<Transform>();
	auto& gateTrans = andEnt.Get<Transform>();
	auto& coilTrans = coilEnt.Get<Transform>();
	auto& tutTrans = tutEnt.Get<Transform>();
	auto& completeTrans = completeEnt.Get<Transform>();
	
	backTrans.SetPositionZ(-39.0f);
	backTrans.SetPositionY(9.0f);

	leftTrans.SetPositionX(-39.0f);
	leftTrans.SetRotationY(90.0f);
	leftTrans.SetPositionY(9.0f);

	rightTrans.SetPositionX(39.0f);
	rightTrans.SetRotationY(90.0f);
	rightTrans.SetPositionY(9.0f);

	auto& camera = camEnt.Get<Camera>();
	auto& orthoCam = uiCamEnt.Get<Camera>();

	camera.LookAt(glm::vec3(playerTrans.GetPositionX(), playerTrans.GetPositionY() + 5.0f, playerTrans.GetPositionZ()));

	auto& meshMain = mainPlayer.Get<MorphRenderer>();
	auto& groundMesh = floorEnt.Get<MeshRenderer>();
	auto& leftMesh = leftEnt.Get<MeshRenderer>();
	auto& rightMesh = rightEnt.Get<MeshRenderer>();
	auto& backMesh = backEnt.Get<MeshRenderer>();
	auto& doorMesh = doorEnt.Get<MorphRenderer>();
	auto& pipeMesh = pipeEnt.Get<MeshRenderer>();
	auto& buttonMesh = buttonEnt.Get<MeshRenderer>();
	auto& buttonMesh2 = buttonEnt2.Get<MeshRenderer>();
	auto& wireMesh = wireEnt.Get<MeshRenderer>();
	auto& wireMesh2 = wireEnt2.Get<MeshRenderer>();
	auto& wireMesh3 = wireEnt3.Get<MeshRenderer>();
	auto& wireMeshP = wirePowered.Get<MeshRenderer>();
	auto& wireMeshP2 = wirePowered2.Get<MeshRenderer>();
	auto& wireMeshP3 = wirePowered3.Get<MeshRenderer>();
	auto& gateMesh = andEnt.Get<MeshRenderer>();
	auto& coilMesh = coilEnt.Get<MeshRenderer>();
	auto& coilMeshP = coilPowered.Get<MeshRenderer>();
	auto& completeMesh = completeEnt.Get<MeshRenderer>();
	auto& tutMesh = tutEnt.Get<MeshRenderer>();


	glm::mat4 transform = playerTrans.GetModelMatrix();
	glm::mat4 transformGround = groundTrans.GetModelMatrix();
	glm::mat4 transformLeft = leftTrans.GetModelMatrix();
	glm::mat4 transformRight = rightTrans.GetModelMatrix();
	glm::mat4 transformBack = backTrans.GetModelMatrix();
	glm::mat4 transformDoor = doorTrans.GetModelMatrix();
	glm::mat4 transformPipe = pipeTrans.GetModelMatrix();
	glm::mat4 transformButton = buttonTrans.GetModelMatrix();
	glm::mat4 transformButton2 = buttonTrans2.GetModelMatrix();
	glm::mat4 transformWire = wireTrans.GetModelMatrix();
	glm::mat4 transformWire2 = wireTrans2.GetModelMatrix();
	glm::mat4 transformWire3 = wireTrans3.GetModelMatrix();
	glm::mat4 transformGate = gateTrans.GetModelMatrix();
	glm::mat4 transformCoil = coilTrans.GetModelMatrix();
	glm::mat4 transformComplete = completeTrans.GetModelMatrix();
	glm::mat4 transformTut = tutTrans.GetModelMatrix();

	auto& particleSystem = particleEnt.Get<ParticleSystem>();

	if (playerTrans.GetPositionX() - buttonTrans.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans.GetPositionZ() > -3.0f)
		button1Watch.Poll(window);

	if (playerTrans.GetPositionX() - buttonTrans2.GetPositionX() < 2.0f && playerTrans.GetPositionX() - buttonTrans2.GetPositionX() > -2.0f
		&& playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() < 3.0f && playerTrans.GetPositionZ() - buttonTrans2.GetPositionZ() > -3.0f)
		button2Watch.Poll(window);

	if (showLevelComplete)
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			levelComplete = true;
			lightNum = 5;
		}
		
	}

#pragma region PlayerMovement

	if (!showLevelComplete)
	{
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

	}
#pragma endregion

#pragma region CameraMovement

	if (camera.GetPosition().z - playerTrans.GetPositionZ() < 10.0f)
		camClose = true;
	else
		camClose = false;

	if (camera.GetPosition().z - playerTrans.GetPositionZ() > 12.5f)
		camFar = true;
	else
		camFar = false;

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

	if (lightNum < 1 || lightNum > 5)
		lightNum = 1;

	playerShader->SetUniform("u_LightNum", lightNum);
	doorShader->SetUniform("u_LightNum", lightNum);
	floorShader->SetUniform("u_LightNum", lightNum);
	levelShader->SetUniform("u_LightNum", lightNum);
	gateShader->SetUniform("u_LightNum", lightNum);
	wireShader->SetUniform("u_LightNum", lightNum);
	untexturedShader->SetUniform("u_LightNum", lightNum);
	buttonShader->SetUniform("u_LightNum", lightNum);

#pragma region Renders
	if (!showLevelComplete)
	{
		playerShader->Bind();
		playerShader->SetUniform("s_Diffuse", 0);
		drumstickMat.Albedo->Bind(0);
		meshMain.Render(camera, transform);

		floorShader->Bind();
		floorShader->SetUniform("s_Diffuse", 0);
		floorMat.Albedo->Bind(0);
		groundMesh.Render(camera, transformGround);

		doorShader->Bind();
		doorShader->SetUniform("s_Diffuse", 0);
		doorMat.Albedo->Bind(0);
		doorMesh.Render(camera, transformDoor);
		doorMat.Albedo->Unbind(0);

		untexturedShader->Bind();
		pipeMesh.Render(camera, transformPipe);

		if (wireEnt3.Get<Wire>().GetIsPowered())
			coilMeshP.Render(camera, transformCoil);
		else
			coilMesh.Render(camera, transformCoil);

		gateMesh.Render(camera, transformGate);
		tutMesh.Render(camera, transformTut);

		wireShader->Bind();
		wireShader->SetUniform("s_Diffuse", 0);
		wireMat.Albedo->Bind(0);

		if (wireEnt.Get<Wire>().GetIsPowered())
			wireMeshP.Render(camera, transformWire);
		else
			wireMesh.Render(camera, transformWire);

		if (wireEnt2.Get<Wire>().GetIsPowered())
			wireMeshP2.Render(camera, transformWire2);
		else
			wireMesh2.Render(camera, transformWire2);

		if (wireEnt3.Get<Wire>().GetIsPowered())
			wireMeshP3.Render(camera, transformWire3);
		else
			wireMesh3.Render(camera, transformWire3);

		buttonShader->Bind();
		buttonShader->SetUniform("s_Diffuse", 0);
		buttonMat.Albedo->Bind(0);
		buttonMesh.Render(camera, transformButton);
		buttonMesh2.Render(camera, transformButton2);

		

		particleSystem.Update(dt, camera);

		if (!andEnt.Get<AndGate>().GetOutput())
		{
			particleShader->Bind();
			glDisable(GL_DEPTH_TEST);
			particleSystem.Draw(camera, particleShader);
			glEnable(GL_DEPTH_TEST);
		}
	}

	levelShader->Bind();
	levelShader->SetUniform("s_Diffuse", 0);
	wallMat.Albedo->Bind(0);
	leftMesh.Render(camera, transformLeft);
	rightMesh.Render(camera, transformRight);
	backMesh.Render(camera, transformBack);

	if (showLevelComplete)
	{
		lightNum = 1;
		levelShader->SetUniform("s_Diffuse", 0);
		completeMat.Albedo->Bind(0);
		completeMesh.Render(orthoCam, transformComplete);
	}


#pragma endregion

	leftEnt.Get<AABB>().Update();
	rightEnt.Get<AABB>().Update();
	backEnt.Get<AABB>().Update();
	doorEnt.Get<AABB>().Update();
	andEnt.Get<AABB>().Update();
	coilEnt.Get<AABB>().Update();
	buttonEnt.Get<Lever>().Update();
	buttonEnt2.Get<Lever>().Update();
	wireEnt.Get<Wire>().Update();
	wireEnt2.Get<Wire>().Update();
	wireEnt3.Get<Wire>().Update();
	andEnt.Get<AndGate>().Update();

	if (doorEnt.Get<Door>().GetOpen())
		doorEnt.Get<MorphAnimation>().Update(dt);

	if (doorEnt.Get<AABB>().GetComplete())
		showLevelComplete = true;
}

void Level1::Unload()
{
	if (scene != nullptr)
	{
		delete scene;

		scene = nullptr;
	}
}

