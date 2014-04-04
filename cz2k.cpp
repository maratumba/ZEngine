#include "cz2k.h"
#include "csdlblitter.h"
#include "csdlsprite.h"
#include "cz2kboard.h"

#include <SDL.h>
#include <iostream>
#include <unistd.h>

CZ2k::CZ2k()
	:Blitter_(new CSDLBlitter)
	,Board_(new CZ2kBoard)
{
	if(!Init())
		return;

	std::string f;
	CSDLSprite *s;

	f = "./data/0.bmp";
	s = new CSDLSprite(0, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(0, s));

	f = "./data/2.bmp";
	s = new CSDLSprite(2, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(2, s));

	f = "./data/4.bmp";
	s = new CSDLSprite(4, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(4, s));

	f = "./data/8.bmp";
	s = new CSDLSprite(8, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(8, s));

	f = "./data/16.bmp";
	s = new CSDLSprite(16, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(16, s));
	
	f = "./data/32.bmp";
	s = new CSDLSprite(32, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(32, s));
	
	f = "./data/64.bmp";
	s = new CSDLSprite(64, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(64, s));
	
	f = "./data/128.bmp";
	s = new CSDLSprite(128, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(128, s));
	
	f = "./data/256.bmp";
	s = new CSDLSprite(256, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(256, s));
	
	f = "./data/512.bmp";
	s = new CSDLSprite(512, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(512, s));
	
	f = "./data/1024.bmp";
	s = new CSDLSprite(1024, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(1024, s));
	
	f = "./data/2048.bmp";
	s = new CSDLSprite(2048, dynamic_cast<CSDLBlitter*>(Blitter_));
	s->LoadImage(f);
	Sprites_.insert(std::pair<int, CSDLSprite*>(2048, s));
}

CZ2k::~CZ2k()
{
	delete Board_;
	delete Blitter_;
	for(auto i: Sprites_)
		delete i.second;
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

		CheckKeyEvents();
		Loop();
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

void CZ2k::CheckKeyEvents()
{
	const unsigned char *keys = SDL_GetKeyboardState(NULL);
	this->UpdateKeybState(keys);
}

void CZ2k::UpdateKeybState(const unsigned char *keys)
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
	Board_->Draw(Sprites_);
	Blitter_->Draw();
}

void CZ2k::Loop()
{
}

