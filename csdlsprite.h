#ifndef __CSDLSPRITE_H__
#define __CSDLSPRITE_H__

#include "cdrawable.h"
#include <string>

class CSDLBlitter;
struct SDL_Texture;

class CSDLSprite: public CDrawable
{
public:
	CSDLSprite(CSDLBlitter *blitter, std::string &file);
	virtual ~CSDLSprite();

	int Draw();
	int DrawFrame(int frameno);

private:
	int LoadImage(std::string &file);

	SDL_Texture *texture = nullptr;
	CSDLBlitter *blitter = nullptr;
};

#endif

