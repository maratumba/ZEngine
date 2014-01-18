#ifndef __CSDLSPRITE_H__
#define __CSDLSPRITE_H__

#include "cdrawable.h"
#include <string>

class CSDLBlitter;
struct SDL_Texture;

class CSDLSprite: public CDrawable
{
public:
	CSDLSprite(CSDLBlitter *blitter);
	virtual ~CSDLSprite();

	int LoadImage(std::string &file);
	int Draw() override;
	int DrawFrame(int frameno);

private:

	SDL_Texture *Texture_ = nullptr;
	CSDLBlitter *Blitter_ = nullptr;
};

#endif

