#ifndef __CZENGINE_H__
#define __CZENGINE_H__

union SDL_Event;

class CBlitter;
class CDrawable;
class CSpriteAnim;
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

	bool isRunning;
	CBlitter *blitter = nullptr;
	CSpriteAnim *stickman = nullptr;
	CDrawable *background = nullptr;
	CCharacter *guybrush = nullptr;
};

#endif

