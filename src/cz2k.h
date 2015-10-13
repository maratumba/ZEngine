#ifndef CZ2K_H
#define CZ2K_H

#include <map>

union SDL_Event;

class CBlitter;
class CSDLInputSink;

class CZ2kBoard;

class CZ2k
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
	void Loop(int usec);

	bool isRunning_ = false;
	CBlitter *Blitter_ = nullptr;
	CZ2kBoard *Board_ = nullptr;
};

#endif
