#ifndef __CSPRITEANIM_H__
#define __CSPRITEABIM_H__

#include "csdlsprite.h"
#include <chrono>

class CSpriteAnim: public CSDLSprite
{
public:
	CSpriteAnim(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod);
	virtual ~CSpriteAnim();

	int Draw();

private:
	int NumFrames = 0;
	double FramePeriod = 0;
	std::chrono::system_clock::time_point LastFrameTime;
};

#endif

