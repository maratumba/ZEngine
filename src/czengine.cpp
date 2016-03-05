#include "czengine.h"
#include "csdlblitter.h"
#include "csdlsprite.h"
#include "cspriteanim.h"
#include "ccharacter.h"
#include "croom.h"
#include <SDL.h>
#include <iostream>
#include <unistd.h>

CZEngine::CZEngine()
	:blitter(new CSDLBlitter)
{
	if(!Init())
		return;

	Room_ = new CRoom(dynamic_cast<CSDLBlitter*>(blitter));
	Room_->ReadConfig("./data/room_01.xml");
	
	Cafer_ = Room_->characters_[0];
	InputSinks_.push_back(Cafer_);
}

CZEngine::~CZEngine()
{
	Guybrush_ = nullptr;
	Cafer_ = nullptr;

	InputSinks_.clear();

	delete Room_;
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
	if(blitter->Init(1280, 720, 24) != 0)
		return false;
	return true;
}

void CZEngine::Quit()
{
}

void CZEngine::CheckKeyEvents()
{
	const unsigned char *keys = SDL_GetKeyboardState(NULL);
	for(const auto &i : InputSinks_)
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

	Room_->Draw();

	if(Cafer_->GetActiveColliders().size())
	{
		Cafer_->DrawCollisionPolygons(blitter, 255, 0, 0);
	}
	
	blitter->Draw();
}

void CZEngine::Loop()
{
		Cafer_->Collides();

		int dX = 20 * 5;
		int dY = 20 * 3;
		
		int minX = blitter->GetWidth() / 2 - dX;
		int minY = blitter->GetHeight() / 2 - dY;

		int maxX = blitter->GetWidth() / 2 + dX;
		int maxY = blitter->GetHeight() / 2 + dY;
		
		int guyX = Cafer_->GetAbsolutePosX() + (Cafer_->GetSizeX() / 2);
		int guyY = Cafer_->GetAbsolutePosY() + (Cafer_->GetSizeY() / 2);
		
		if(guyX < minX)
			blitter->MoveOffset(3, 0);
		if(guyX > maxX)
			blitter->MoveOffset(-3, 0);
		if(guyY < minY)
			blitter->MoveOffset(0, 3);
		if(guyY > maxY)
			blitter->MoveOffset(0, -3);
}
