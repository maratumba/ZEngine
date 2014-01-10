#ifndef __CSPRITEANIM_H__
#define __CSPRITEANIM_H__

#include "csdlsprite.h"
#include <chrono>

class CSpriteAnim: public CSDLSprite
{
public:
	CSpriteAnim(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod = 0);
	virtual ~CSpriteAnim();

	int Draw() override;

	void SetActiveFrames(int first, int last) {FirstFrame = first; LastFrame = last; CurrentFrame = first;}
	void SetFramePeriod(double frameperiod) {FramePeriod = frameperiod;}
	void StartAnimation() {Running = true;}
	void StopAnimation() {Running = false;}

private:
	bool Running = false;
	int NumFrames = 0;
	int FirstFrame = 0;
	int LastFrame = 0;
	int CurrentFrame = 0;
	double FramePeriod = 0;
	int FrameWidth = 0;
	std::chrono::system_clock::time_point LastFrameTime;
};

#endif

