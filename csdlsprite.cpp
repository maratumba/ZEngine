#include "csdlsprite.h"
#include "csdlblitter.h"
#include <SDL.h>
#include <iostream>

CSDLSprite::CSDLSprite(CSDLBlitter *blitter)
	: CDrawable()
	, Blitter_(blitter)
{
}

CSDLSprite::~CSDLSprite()
{
	SDL_DestroyTexture(Texture_);
	Texture_ = nullptr;
	Blitter_ = nullptr;
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

	SizeX_ = bmp->w;
	SizeY_ = bmp->h;

	Texture_ = SDL_CreateTextureFromSurface(Blitter_->GetRenderer(), bmp);
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
	SDL_Rect srcrect {GetSizeX()*frameno, 0, GetSizeX(), GetSizeY()};
	SDL_Rect destrect {GetPosX(), GetPosY(), GetSizeX()*GetScaleX(), GetSizeY()*GetScaleY()};
	SDL_RenderCopy(Blitter_->GetRenderer(), Texture_, &srcrect, &destrect);
	return 0;
}

