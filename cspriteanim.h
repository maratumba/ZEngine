#ifndef __CSPRITEANIM_H__
#define __CSPRITEABIM_H__

#include "csdlsprite.h"

class CSpriteAnim: public CSDLSprite
{
public:
	CSpriteAnim(CSDLBlitter *blitter, std::string &file);
	virtual ~CSpriteAnim();

	int Draw();

private:
	int NumFrames = 0;
};

#endif

