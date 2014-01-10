#include "cspriteanim.h"
#include <iostream>

CSpriteAnim::CSpriteAnim(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod)
	: CSDLSprite(blitter, file)
	, FramePeriod(frameperiod)
	, FrameWidth(framewidth)
{
	NumFrames = sizex / FrameWidth;
	sizex /= NumFrames;

	FirstFrame = 0;
	LastFrame = NumFrames - 1;

	std::cout << "sizex: " << sizex << std::endl;
	std::cout << "NumFrames: " << NumFrames << std::endl;
}

CSpriteAnim::~CSpriteAnim()
{
}

int CSpriteAnim::Draw()
{
	using namespace std::chrono;

	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<double> d = duration_cast<duration<double>> (now - LastFrameTime);

	if(d.count() > FramePeriod)
	{
		//std::cout << "duration: " << d.count() << std::endl;
		LastFrameTime = now;

		if(Running && (FramePeriod > 0))
		{
			CurrentFrame++;
			if(CurrentFrame > LastFrame)
				CurrentFrame = FirstFrame;
		}
	}

	CSDLSprite::DrawFrame(CurrentFrame);
	return 0;
}

