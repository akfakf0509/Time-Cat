#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

Engine* Engine::GetInstance()
{
	static Engine instance_ = Engine();
	return &instance_;
}

void Engine::Init()
{
	timeM = new TimeManager();
	windowM = new WindowManager();
	graphicM = new GraphicManager();
	inputM = new InputManager();
	soundM = new SoundManager();
	textureM = new TextureManager();
	gameM = new GameManager();
	sceneM = new SceneManager();
}

void Engine::MainLoop()
{
	while (GetWindowM()->IsRunning())
	{
		if (GetWindowM()->MsgLoop())
		{

		}
		timeM->Update();
		soundM->Update();
		textureM->Update();
		inputM->Update();
		sceneM->Update();

		graphicM->Render();
		gameM->Update();
	}
}

void Engine::Release()
{
	SafeDelete(graphicM);
	SafeDelete(inputM);
	SafeDelete(soundM);
	SafeDelete(textureM);
	SafeDelete(timeM);
	SafeDelete(windowM);
	SafeDelete(sceneM);
	SafeDelete(gameM);
}