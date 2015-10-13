#include "cz2k.h"
#include "csdlblitter.h"
#include "csdlsprite.h"
#include "cz2kboard.h"

#include <SDL.h>
#include <iostream>
#include <unistd.h>

CZ2k::CZ2k()
	:Blitter_(new CSDLBlitter)
	,Board_(nullptr)
{
	if(!Init())
		return;
	
	Board_ = new CZ2kBoard(Blitter_); 
}

CZ2k::~CZ2k()
{
	delete Blitter_;
	delete Board_;
}

void CZ2k::Run()
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

		Loop(10000);
		Render();

		usleep(10000);
	}
	Quit();
}

bool CZ2k::Init()
{
	if(Blitter_->Init(1024/2, 1024/2, 24) != 0)
		return false;
	return true;
}

void CZ2k::Quit()
{
}

void CZ2k::OnEvent(SDL_Event *event)
{
	switch(event->type)
	{
	case SDL_KEYUP:
		{
			switch(event->key.keysym.sym)
			{
			case SDLK_ESCAPE: isRunning_ = false; break;
			case SDLK_UP   : Board_->MoveUp(); break;
			case SDLK_DOWN : Board_->MoveDown(); break;
			case SDLK_RIGHT: Board_->MoveRight(); break;
			case SDLK_LEFT : Board_->MoveLeft(); break;
			default: break;
			}
		}break;
	case SDL_QUIT:
		isRunning_ = false; break;
	default: break;
	}
}

void CZ2k::Render()
{
	Blitter_->Clear();
	Board_->Draw();
	Blitter_->Draw();
}

void CZ2k::Loop(int usec)
{
	Board_->Tick(usec);
}

