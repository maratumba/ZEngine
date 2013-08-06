#include "csdlsprite.h"
#include "csdlblitter.h"
#include <SDL.h>
#include <iostream>

CSDLSprite::CSDLSprite(CSDLBlitter *blitter, std::string &file)
{
	this->blitter = blitter;
	LoadImage(file);
}

CSDLSprite::~CSDLSprite()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	blitter = nullptr;
}

int CSDLSprite::LoadImage(std::string &file)
{
	SDL_Surface *bmp = nullptr;
	bmp = SDL_LoadBMP(file.c_str());
	if(bmp == nullptr)
	{
		std::cout << file.c_str() << ": file not found" << std::endl;
		return 1;
	}

	sizex = bmp->w;
	sizey = bmp->h;

	texture = SDL_CreateTextureFromSurface(blitter->GetRenderer(), bmp);
	SDL_FreeSurface(bmp);

	std::cout << "image loaded: " << file.c_str() << std::endl;
	return 0;
}

int CSDLSprite::Draw()
{
	DrawFrame(0);
	return 0;
}

int CSDLSprite::DrawFrame(int frameno)
{
	SDL_Rect srcrect {sizex*frameno, 0, sizex, sizey};
	SDL_Rect destrect {posx, posy, sizex, sizey};
	SDL_RenderCopy(blitter->GetRenderer(), texture, &srcrect, &destrect);
	return 0;
}

