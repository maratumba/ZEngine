#include "ccharacter.h"
#include <SDL.h>

enum class eAnimState
{
	StandRight,
	StandLeft,
	WalkRight,
	WalkLeft
};

CCharacter::CCharacter(CSDLBlitter *blitter, std::string &file, int framewidth, double frameperiod)
	:CSpriteAnim(blitter, file, framewidth, frameperiod)
	,State(eAnimState::StandRight)
{
}

CCharacter::~CCharacter()
{
}

void CCharacter::UpdateKeybState(const unsigned char *keys)
{
	if(keys[SDL_SCANCODE_RIGHT])
	{
		this->MoveRight(2);

		if(State != eAnimState::WalkRight)
			this->SetActiveFrames(1, 6);
		State = eAnimState::WalkRight;

		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_LEFT])
	{
		this->MoveLeft(2);

		if(State != eAnimState::WalkLeft)
			this->SetActiveFrames(1, 6);
		State = eAnimState::WalkLeft;

		this->StartAnimation();
	}
	else
	{
		this->SetActiveFrames(0, 0);
		this->StopAnimation();
		State = eAnimState::StandRight;
	}
}

