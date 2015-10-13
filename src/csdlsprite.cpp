#include "csdlsprite.h"
#include "csdlblitter.h"
#include <SDL.h>
#include <iostream>

CSDLSprite::CSDLSprite(int id, CSDLBlitter *blitter)
	:CDrawable()
	,CCollider(id)
	,Blitter_(blitter)
{
}

CSDLSprite::~CSDLSprite()
{
	SDL_DestroyTexture(Texture_);
	Texture_ = nullptr;
	Blitter_ = nullptr;
}

int CSDLSprite::ReadConfig(const rapidxml::xml_node<> *node)
{
	using namespace rapidxml;

	std::cout << "Reading CSDLSprite" << std::endl;
	xml_node<> *poly = node->first_node("polygon");
	do
	{
		CPolygon polygon;

		//std::cout << "poly" << std::endl;
		xml_node<> *point = poly->first_node("point");
		do
		{
			//std::cout << "point" << std::endl;

			tPoint p;
			xml_attribute<> *att;
			att = point->first_attribute("x");
			if(att)
				p.first = atol(att->value());
			//std::cout << "x          : " << p.first << std::endl;
			att = point->first_attribute("y");
			if(att)
				p.second = atol(att->value());
			//std::cout << "y          : " << p.second << std::endl;

			polygon.AddPoint(p);

			point = point->next_sibling("point");
		}while(point);

		AddCollisionPolygon(polygon);

		poly = poly->next_sibling("polygon");
	}while(poly);

	DumpCollisionPolygons();

	return 0;
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
	int srcX = GetSizeX() * frameno;
	int srcY = 0;
	int srcW = GetSizeX();
	int srcH = GetSizeY();
	
	int dstW = GetSizeX() * GetScaleX();
	int dstH = GetSizeY() * GetScaleY();
	int dstX;
	int dstY;

	switch(AnchorPos_)
	{
		case CDrawable::AnchorPos::TOP_LEFT:
			dstX = GetPosX() + Blitter_->GetOffsetX();
			dstY = GetPosY() + Blitter_->GetOffsetY();
			break;
		case CDrawable::AnchorPos::CENTER:
			dstX = GetPosX() + Blitter_->GetOffsetX() + (srcW - dstW) / 2;
			dstY = GetPosY() + Blitter_->GetOffsetY() + (srcH - dstH) / 2;
			break;
		default:
			dstX = 0;
			dstY = 0;
	};

	SDL_Rect srcrect {srcX, srcY, srcW, srcH};
	SDL_Rect dstrect {dstX, dstY, dstW, dstH};

	int rvl = SDL_RenderCopy(Blitter_->GetRenderer(), Texture_, &srcrect, &dstrect);
	if(rvl)
		std::cout << "SDL Failed to draw the sprite: " << SDL_GetError() << std::endl;

	return 0;
}

void CSDLSprite::DrawCollisionPolygons(CBlitter *blitter)
{
	for(auto &poly : CollisionPolygons_)
	{
		tPoint *prevPoint = &poly.Points_[poly.Points_.size() - 1];
		for(auto &point : poly.Points_)
		{
			blitter->DrawLine(
					GetPosX() + Blitter_->GetOffsetX() + prevPoint->first, 
					GetPosY() + Blitter_->GetOffsetY() + prevPoint->second, 
					GetPosX() + Blitter_->GetOffsetX() + point.first, 
					GetPosY() + Blitter_->GetOffsetY() + point.second);
			prevPoint = &point;
		}
	}
}

