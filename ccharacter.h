#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "cspriteanim.h"
#include "csdlinputsink.h"

#include "rapidxml.hpp"

enum class eAnimState;

class CCharacter: public CSpriteAnim, public CSDLInputSink
{
public:
	CCharacter(int id, CSDLBlitter *blitter, std::vector<CSDLSprite*> &colliders);
	virtual ~CCharacter();

	void UpdateKeybState(const unsigned char *keys) override;

	int ReadConfig(std::string &file);
	int Init(std::string &file, int framewidth, double frameperiod);
	bool Collides();

private:
	eAnimState State_;
	std::vector<CSDLSprite*> &Colliders_;

	int ReadConfig(const rapidxml::xml_node<> *node);
	void SetAnimState(eAnimState state);
};

#endif
