#include "czengine.h"
#include "csdlblitter.h"
#include "csdlsprite.h"
#include "cspriteanim.h"
#include "ccharacter.h"
#include <SDL.h>
#include <iostream>
#include <unistd.h>

CZEngine::CZEngine()
	:blitter(new CSDLBlitter)
{
	if(!Init())
		return;

	std::string f;
	std::string c;
	f = "./data/CitadelIsland.bmp";
	CSDLSprite *background = new CSDLSprite(1, dynamic_cast<CSDLBlitter*>(blitter));
	background->LoadImage(f);
	background->SetPos(-3000, -2500);
	Sprites_.push_back(background);

	f = "./data/stickman.bmp";
	CSpriteAnim *stickman = new CSpriteAnim(2, dynamic_cast<CSDLBlitter*>(blitter));
	c = "./data/stickman.xml";
	stickman->ReadConfig(c);
	//stickman->Init(f, 40, 1);
	stickman->SetPos(100, 400);
	stickman->SetActiveFrames(0,1);
	stickman->StartAnimation();
	Sprites_.push_back(stickman);

	Guybrush_ = new CCharacter(3, dynamic_cast<CSDLBlitter*>(blitter), Sprites_);
	c = "./data/guybrush.xml";
	Guybrush_->ReadConfig(c);
	//Guybrush_->Init(f, 100, 0.15);
	Guybrush_->SetPos(300, 400);
	Sprites_.push_back(Guybrush_);
	InputSinks_.push_back(Guybrush_);
}

CZEngine::~CZEngine()
{
	Guybrush_ = nullptr;
	for(auto &i : Sprites_)
	{
		delete i;
	}
	Sprites_.clear();
	InputSinks_.clear();

	delete blitter;
}

void CZEngine::Run()
{
	std::cout << "init done" << std::endl;

	SDL_Event event;
	isRunning_ = true;
	while(isRunning_)
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
	for(auto &i : InputSinks_)
	{
		i->UpdateKeybState(keys);
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
			case SDLK_ESCAPE: isRunning_ = false; break;
			default: break;
			}
		}break;
	case SDL_QUIT:
		isRunning_ = false; break;
	default: break;
	}
}

void CZEngine::Render()
{
	blitter->Clear();

	for(auto &i : Sprites_)
	{
		i->Draw();
	}
	for(auto &i : Sprites_)
	{
		i->DrawCollisionPolygons(blitter);
	}

	blitter->Draw();
}

void CZEngine::Loop()
{
		int dX = 20 * 5;
		int dY = 20 * 3;
		
		int minX = blitter->GetWidth() / 2 - dX;
		int minY = blitter->GetHeight() / 2 - dY;

		int maxX = blitter->GetWidth() / 2 + dX;
		int maxY = blitter->GetHeight() / 2 + dY;
		
		int guyX = Guybrush_->GetAbsolutePosX() + (Guybrush_->GetSizeX() / 2);
		int guyY = Guybrush_->GetAbsolutePosY() + (Guybrush_->GetSizeY() / 2);
		
		if(guyX < minX)
			blitter->MoveOffset(3, 0);
		if(guyX > maxX)
			blitter->MoveOffset(-3, 0);
		if(guyY < minY)
			blitter->MoveOffset(0, 3);
		if(guyY > maxY)
			blitter->MoveOffset(0, -3);
}


