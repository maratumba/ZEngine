#ifndef __CSPRITEANIM_H__
#define __CSPRITEANIM_H__

#include "csdlsprite.h"

#include "rapidxml.hpp"

#include <chrono>

class CSpriteAnim: public CSDLSprite
{
public:
	CSpriteAnim(int id, CSDLBlitter *blitter);
	virtual ~CSpriteAnim();

	int Draw() override;

	int Init(std::string &file, int framewidth, double frameperiod = 0, bool looping = true);
	void SetActiveFrames(int first, int last) {FirstFrame_ = first; LastFrame_ = last; CurrentFrame_ = first;}
	void SetFramePeriod(double frameperiod) {FramePeriod_ = frameperiod;}
	void StartAnimation() {Running_ = true;}
	void StopAnimation() {Running_ = false;}

	int ReadConfig(const std::string &file);

protected:
	int ReadConfig(const rapidxml::xml_node<> *node);

private:
	bool Running_ = false;
	bool Looping_ = true;
	int NumFrames_ = 0;
	int FirstFrame_ = 0;
	int LastFrame_ = 0;
	int CurrentFrame_ = 0;
	double FramePeriod_ = 0;
	int FrameWidth_ = 0;
	std::chrono::system_clock::time_point LastFrameTime_;
};

#endif

