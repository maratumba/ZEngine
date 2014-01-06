#include "cspriteanim.h"
#include <iostream>

CSpriteAnim::CSpriteAnim(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod)
	: CSDLSprite(blitter, file)
	, FramePeriod(frameperiod)
{
	NumFrames = sizex / framewidth;
	sizex /= NumFrames;

	std::cout << "sizex: " << sizex << std::endl;
	std::cout << "NumFrames: " << NumFrames << std::endl;
}

CSpriteAnim::~CSpriteAnim()
{
}

int CSpriteAnim::Draw()
{
	using namespace std::chrono;
	static int frameno = 0;

	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<double> d = duration_cast<duration<double>> (now - LastFrameTime);

	if(d.count() > FramePeriod)
	{
		//std::cout << "duration: " << d.count() << std::endl;
		LastFrameTime = now;
		frameno = (frameno + 1) % (NumFrames - 1);
	}

	CSDLSprite::DrawFrame(frameno+1);
	return 0;
}

