#ifndef CCHARACTERH
#define CCHARACTERH

#include "cspriteanim.h"
#include "csdlinputsink.h"

enum class eAnimState;

class CCharacter: public CSpriteAnim, CSDLInputSink
{
public:
	CCharacter(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod);
	virtual ~CCharacter();

	void UpdateKeybState(const unsigned char *keys) override;

private:
	eAnimState State;
};

#endif

