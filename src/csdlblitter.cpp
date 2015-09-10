#include "csdlblitter.h"
#include <SDL.h>
#include <iostream>

CSDLBlitter::CSDLBlitter()
	:CBlitter()
{
}

CSDLBlitter::~CSDLBlitter()
{
	SDL_DestroyRenderer(Renderer_);
	SDL_DestroyWindow(Window_);
}

int CSDLBlitter::Init(int width, int height, int bpp)
{
	ViewWidth_ = width;
	ViewHeight_ = height;
	ViewBpp_ = bpp;

	std::cout << "initing sdl2" << std::endl;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "creating window" << std::endl;

	Window_ = SDL_CreateWindow("ZEngine",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			ViewWidth_,ViewHeight_,
			SDL_WINDOW_SHOWN);
	if(!Window_)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "creating renderer" << std::endl;

	Renderer_ = SDL_CreateRenderer(Window_, -1, SDL_RENDERER_ACCELERATED);
	if(!Renderer_)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

int CSDLBlitter::Clear()
{
	int rvl = SDL_RenderClear(Renderer_);
	if(rvl)
		std::cout << SDL_GetError() << std::endl;
	return rvl;
}

int CSDLBlitter::Draw()
{
	SDL_RenderPresent(Renderer_);
	return 0;
}

void CSDLBlitter::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(Renderer_, x1, y1, x2, y2);
}

void CSDLBlitter::SetDrawColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(Renderer_, r, g, b, a);
}

