#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "cspriteanim.h"
#include "csdlinputsink.h"
#include "ccollider.h"

enum class eAnimState;

class CCharacter: public CSpriteAnim, CSDLInputSink, CCollider
{
public:
	CCharacter(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod);
	virtual ~CCharacter();

	void UpdateKeybState(const unsigned char *keys) override;

private:
	eAnimState State;

	int ReadConfig(std::string file);
	void SetAnimState(eAnimState state);
};

#endif

