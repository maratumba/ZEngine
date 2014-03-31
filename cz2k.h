#ifndef CZ2K_H
#define CZ2K_H

#include "csdlinputsink.h"
#include <map>

union SDL_Event;

class CBlitter;
class CSDLSprite;
class CSDLInputSink;

class CZ2kBoard;

class CZ2k: public CSDLInputSink
{
public:
	CZ2k();
	~CZ2k();
	void Run();

private:
	bool Init();
	void Quit();
	void CheckKeyEvents();
	void OnEvent(SDL_Event *event);
	void Render();
	void Loop();

	void UpdateKeybState(const unsigned char *keys) override;

	bool isRunning_ = false;
	CBlitter *Blitter_ = nullptr;
	CZ2kBoard *Board_ = nullptr;
	
	std::map<int, CSDLSprite*> Sprites_;
};

#endif
