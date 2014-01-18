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

	virtual int Init(int width, int height, int bpp) override;
	virtual int Clear() override;
	virtual int Draw() override;
	virtual int DrawLine(int x1, int y1, int x2, int y2) override;

	SDL_Renderer *GetRenderer() {return Renderer_;}

private:
	SDL_Window *Window_ = nullptr;
	SDL_Renderer *Renderer_ = nullptr;
};

#endif

