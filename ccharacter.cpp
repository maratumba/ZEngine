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
void CCharacter::SetAnimState(eAnimState state)
{
	switch(state)
	{
	case eAnimState::WalkRight:
		if(this->State != eAnimState::WalkRight)
			this->SetActiveFrames(1, 6);
		this->State = eAnimState::WalkRight;
		break;

	case eAnimState::WalkLeft:
		if(this->State != eAnimState::WalkLeft)
			this->SetActiveFrames(8, 13);
		this->State = eAnimState::WalkLeft;
		break;

	case eAnimState::StandRight:
		this->SetActiveFrames(0, 0);
		this->State = eAnimState::StandRight;
		break;

	case eAnimState::StandLeft:
		this->SetActiveFrames(7, 7);
		this->State = eAnimState::StandLeft;
		break;
	
	default:
		break;
	}
}

void CCharacter::UpdateKeybState(const unsigned char *keys)
{
	if(keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_UP])
	{
		this->MoveRight(1);
		this->MoveUp(1);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_DOWN])
	{
		this->MoveRight(1);
		this->MoveDown(1);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_UP])
	{
		this->MoveLeft(1);
		this->MoveUp(1);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_DOWN])
	{
		this->MoveLeft(1);
		this->MoveDown(1);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	if(keys[SDL_SCANCODE_RIGHT])
	{
		this->MoveRight(2);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_LEFT])
	{
		this->MoveLeft(2);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_UP])
	{
		this->MoveUp(2);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_DOWN])
	{
		this->MoveDown(2);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else
	{
		if(State == eAnimState::WalkRight)
			this->SetAnimState(eAnimState::StandRight);
		if(State == eAnimState::WalkLeft)
			this->SetAnimState(eAnimState::StandLeft);
		//this->StopAnimation();
	}
}

