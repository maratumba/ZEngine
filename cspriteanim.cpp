#include "cspriteanim.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <iostream>

CSpriteAnim::CSpriteAnim(int id, CSDLBlitter *blitter)
	: CSDLSprite(id, blitter)
{
}

CSpriteAnim::~CSpriteAnim()
{
}

int CSpriteAnim::ReadConfig(std::string &file)
{
	using namespace rapidxml;

	rapidxml::file<> f(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(f.data());

	xml_node<> *root = doc.first_node("spriteanim");
	if(!root)
		return 1;
	
	ReadConfig(root);
	return 0;
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

int CSpriteAnim::Init(std::string &file, int framewidth, double frameperiod, bool looping)
{
	int rvl = CSDLSprite::LoadImage(file);
	if(rvl != 0)
		return rvl;

	FramePeriod_ = frameperiod;
	FrameWidth_ = framewidth;
	Looping_ = looping;

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
			{
				if(Looping_)
					CurrentFrame_ = FirstFrame_;
				else
					Running_ = false;
			}
		}
	}

	CSDLSprite::DrawFrame(CurrentFrame_);
	return 0;
}

