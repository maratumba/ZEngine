#include "cspriteanim.h"
#include <iostream>

CSpriteAnim::CSpriteAnim(CSDLBlitter *blitter)
	: CSDLSprite(blitter)
{
}

CSpriteAnim::~CSpriteAnim()
{
}

int CSpriteAnim::Init(std::string &file, int framewidth, double frameperiod)
{
	int rvl = CSDLSprite::LoadImage(file);
	if(rvl != 0)
		return rvl;

	FramePeriod_ = frameperiod;
	FrameWidth_ = framewidth;

	NumFrames_ = SizeX_ / FrameWidth_;
	SizeX_ = FrameWidth_;

	FirstFrame_ = 0;
	LastFrame_ = NumFrames_ - 1;

	std::cout << "sizex: " << SizeX_ << std::endl;
	std::cout << "NumFrames: " << NumFrames_ << std::endl;

	return rvl;
}

int CSpriteAnim::Draw()
{
	using namespace std::chrono;

	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<double> d = duration_cast<duration<double>> (now - LastFrameTime_);

	if(d.count() > FramePeriod_)
	{
		//std::cout << "duration: " << d.count() << std::endl;
		LastFrameTime_ = now;

		if(Running_ && (FramePeriod_ > 0))
		{
			CurrentFrame_++;
			if(CurrentFrame_ > LastFrame_)
				CurrentFrame_ = FirstFrame_;
		}
	}

	CSDLSprite::DrawFrame(CurrentFrame_);
	return 0;
}

