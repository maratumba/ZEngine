#include "cspriteanim.h"
#include <iostream>

CSpriteAnim::CSpriteAnim(CSDLBlitter *blitter, std::string &file)
	: CSDLSprite(blitter, file)
{
	std::cout << "sizex: " << sizex << std::endl;
	std::cout << "NumFrames: " << NumFrames << std::endl;

	NumFrames = sizex / 100;
	sizex /= NumFrames;
}

CSpriteAnim::~CSpriteAnim()
{
}

int CSpriteAnim::Draw()
{
	static int frameno = 0;
	CSDLSprite::DrawFrame(frameno);
	frameno = (frameno + 1) % NumFrames;
	return 0;
}

