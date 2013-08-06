#include "csdlblitter.h"
#include <SDL.h>
#include <iostream>

CSDLBlitter::CSDLBlitter()
{
}

CSDLBlitter::~CSDLBlitter()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int CSDLBlitter::Init(int width, int height, int bpp)
{
	std::cout << "initing sdl2" << std::endl;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "creating window" << std::endl;

	window = SDL_CreateWindow("ZEngine",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,height,
			SDL_WINDOW_SHOWN);
	if(!window)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "creating renderer" << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

int CSDLBlitter::Clear()
{
	int rvl = SDL_RenderClear(renderer);
	if(rvl)
		std::cout << SDL_GetError() << std::endl;
	return rvl;
}

int CSDLBlitter::Draw()
{
	SDL_RenderPresent(renderer);
	return 0;
}

