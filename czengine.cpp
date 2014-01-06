#include "czengine.h"
#include "csdlblitter.h"
#include "csdlsprite.h"
#include "cspriteanim.h"
#include <SDL.h>
#include <iostream>
#include <unistd.h>

int main()
{
	CZEngine e;
	e.Run();
	return 0;
}

CZEngine::CZEngine()
{
	isRunning = false;
	blitter = new CSDLBlitter;


	if(!Init())
		return;

	std::string f;
	f = "./data/stickman.bmp";
	stickman = new CSDLSprite(dynamic_cast<CSDLBlitter*>(blitter), f);
	stickman->SetPos(100, 400);

	f = "./data/guybrush.bmp";
	guybrush = new CSpriteAnim(dynamic_cast<CSDLBlitter*>(blitter), f, 100, 0.15);
	guybrush->SetPos(300, 400);
}

CZEngine::~CZEngine()
{
	delete stickman;
	delete guybrush;

	delete blitter;
}

void CZEngine::Run()
{
	std::cout << "init done" << std::endl;

	SDL_Event event;
	isRunning = true;
	while(isRunning)
	{
		while(SDL_PollEvent(&event))
		{
			OnEvent(&event);
			usleep(1);
		}

		CheckKeyEvents();
		Loop();
		Render();

		usleep(10000);
	}
	Quit();
}

bool CZEngine::Init()
{
	if(blitter->Init(1024, 768, 24) != 0)
		return false;
	return true;
}

void CZEngine::Quit()
{
}

void CZEngine::CheckKeyEvents()
{
	const unsigned char *keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_RIGHT])
	{
		//stickman->MoveRight(10);
		guybrush->MoveRight(2);
	}
	if(keys[SDL_SCANCODE_LEFT])
	{
		//stickman->MoveLeft(10);
		guybrush->MoveLeft(3);
	}
}

void CZEngine::OnEvent(SDL_Event *event)
{
	switch(event->type)
	{
	case SDL_KEYUP:
		{
			switch(event->key.keysym.sym)
			{
			case SDLK_ESCAPE: isRunning = false; break;
			default: break;
			}
		}break;
	case SDL_QUIT:
		isRunning = false; break;
	default: break;
	}
}

void CZEngine::Render()
{
	blitter->Clear();
	stickman->Draw();
	guybrush->Draw();
	blitter->Draw();
}

void CZEngine::Loop()
{
}


