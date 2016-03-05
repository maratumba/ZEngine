#ifndef __CZENGINE_H__
#define __CZENGINE_H__

#include <vector>

union SDL_Event;

class CBlitter;
class CSDLSprite;
class CSDLInputSink;
class CCharacter;
class CRoom;

class CZEngine
{
public:
	CZEngine();
	~CZEngine();
	void Run();

private:
	bool Init();
	void Quit();
	void CheckKeyEvents();
	void OnEvent(SDL_Event *event);
	void Render();
	void Loop();

	bool isRunning_ = false;
	CBlitter *blitter = nullptr;
	CCharacter *Guybrush_ = nullptr;
	CCharacter *Cafer_ = nullptr;
	CRoom *Room_ = nullptr;
	
	std::vector<CSDLInputSink*> InputSinks_;
};

#endif

