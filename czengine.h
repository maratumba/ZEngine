#ifndef __CZENGINE_H__
#define __CZENGINE_H__

#include <vector>

union SDL_Event;

class CBlitter;
class CCollider;
class CSDLSprite;
class CSDLInputSink;
class CCharacter;

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

	bool isRunning_;
	CBlitter *blitter = nullptr;
	CCharacter *Guybrush_ = nullptr;
	
	std::vector<CSDLSprite*> Sprites_;
	std::vector<CSDLInputSink*> InputSinks_;
};

#endif

