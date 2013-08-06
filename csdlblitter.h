#ifndef __CSDLBLITTER_H__
#define __CSDLBLITTER_H__

#include "cblitter.h"

union SDL_Event;
struct SDL_Window;
struct SDL_Renderer;

class CSDLBlitter: public CBlitter
{
public:
	CSDLBlitter();
	virtual ~CSDLBlitter();

	virtual int Init(int width, int height, int bpp);
	virtual int Clear();
	virtual int Draw();

	SDL_Renderer *GetRenderer() {return renderer;}

private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};

#endif

