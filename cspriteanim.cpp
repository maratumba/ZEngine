#include "cspriteanim.h"
#include <iostream>

CSpriteAnim::CSpriteAnim(CSDLBlitter *blitter)
	: CSDLSprite(blitter)
{
}

CSpriteAnim::~CSpriteAnim()
{
}

int CSpriteAnim::ReadConfig(const rapidxml::xml_node<> *node)
{
	using namespace rapidxml;
	std::string file = "";
	int framewidth = 0;
	double frameperiod = 0;

	std::cout << "Reading CSpriteAnim" << std::endl;
	xml_attribute<> *att;
	att = node->first_attribute("file");
	if(att)
		file = att->value();
	std::cout << "file       : " << file << std::endl;
	att = node->first_attribute("framewidth");
	if(att)
		framewidth = atol(att->value());
	std::cout << "framewidth : " << framewidth << std::endl;
	att = node->first_attribute("frameperiod");
	if(att)
		frameperiod = atof(att->value());
	std::cout << "frameperiod: " << frameperiod << std::endl;

	int rvl = Init(file, framewidth, frameperiod);

	xml_node<> *sprite = node->first_node("sprite");
	if(sprite)
		CSDLSprite::ReadConfig(sprite);

	return rvl;
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

