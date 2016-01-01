#include "ccharacter.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <SDL.h>
#include <iostream>

enum class eAnimState
{
	StandRight,
	StandLeft,
	WalkRight,
	WalkLeft
};

CCharacter::CCharacter(int id, CSDLBlitter *blitter, std::vector<CSDLSprite*> &colliders)
	:CSpriteAnim(id, blitter)
	,CSDLInputSink()
	,State_(eAnimState::StandRight)
	,Colliders_(colliders)
{
}

CCharacter::~CCharacter()
{
}

int CCharacter::Init(std::string &file, int framewidth, double frameperiod)
{
	return CSpriteAnim::Init(file, framewidth, frameperiod);
}

int CCharacter::ReadConfig(std::string &file)
{
	using namespace rapidxml;

	rapidxml::file<> f(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(f.data());

	xml_node<> *root = doc.first_node("character");
	if(!root)
		return 1;
	
	ReadConfig(root);
	return 0;
}

int CCharacter::ReadConfig(const rapidxml::xml_node<> *node)
{
	std::cout << "Reading CCharacter" << std::endl;
	rapidxml::xml_node<> *anim = node->first_node("spriteanim");
	if(!anim)
		return 1;

	int rvl = CSpriteAnim::ReadConfig(anim);
	
	rapidxml::xml_node<> *aniframe = node->first_node("aniframe");
	while(aniframe)
	{
		std::string name;
		int frameFirst = 0;
		int frameLast = 0;
		rapidxml::xml_attribute<> *att;
		att = aniframe->first_attribute("name");
		if(!att)
			break;
		name = att->value();

		att = aniframe->first_attribute("frameFirst");
		if(!att)
			break;
		frameFirst = atoi(att->value());
		
		att = aniframe->first_attribute("frameLast");
		if(!att)
			break;
		frameLast = atoi(att->value());
	
		//AniFrames_.insert(std::make_pair(name, std::make_pair(frameFirst, frameLast)));
		AniFrames_[name] = std::make_pair(frameFirst, frameLast);
		std::cout << "aniframe " << name << std::endl;
		
		aniframe = aniframe->next_sibling("aniframe");
	}
	
	std::cout << "Reading CCharacter done" << std::endl;
	return rvl;
}

bool CCharacter::Collides()
{
	for(auto &coll : Colliders_)
	{
		if(GetId() == coll->GetId())
			continue;

		tPoint thisPos;
		thisPos.first = this->GetPosX();
		thisPos.second = this->GetPosY();
		tPoint otherPos;
		otherPos.first = coll->GetPosX();
		otherPos.second = coll->GetPosY();
		
		bool rvl = CollidesWith(thisPos, *coll, otherPos);
		if(rvl)
		{
			//std::cout << "This " << GetId() << " collides with " << coll->GetId() << std::endl;
			return true;
		}
	}
	return false;
}

void CCharacter::SetAnimState(std::string state)
{
	std::pair<int, int> f;
	try
	{
		f = AniFrames_.at(state);
	}
	catch(const std::exception &e)
	{
		std::cout << "Exception caught!!!: " << e.what() << std::endl;
	}
	this->SetActiveFrames(f.first, f.second);
}

void CCharacter::SetAnimState(eAnimState state)
{
	switch(state)
	{
	case eAnimState::WalkRight:
		if(this->State_ != eAnimState::WalkRight)
			this->SetAnimState("WalkRight");
		this->State_ = eAnimState::WalkRight;
		break;

	case eAnimState::WalkLeft:
		if(this->State_ != eAnimState::WalkLeft)
			this->SetAnimState("WalkLeft");
		this->State_ = eAnimState::WalkLeft;
		break;

	case eAnimState::StandRight:
		this->SetAnimState("StandRight");
		this->State_ = eAnimState::StandRight;
		break;

	case eAnimState::StandLeft:
		this->SetAnimState("StandLeft");
		this->State_ = eAnimState::StandLeft;
		break;
	
	default:
		break;
	}
}

void CCharacter::UpdateKeybState(const unsigned char *keys)
{
		if(this->Collides())
		{;}//std::cout << "Collides" << std::endl;

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
		if(State_ == eAnimState::WalkRight)
			this->SetAnimState(eAnimState::StandRight);
		if(State_ == eAnimState::WalkLeft)
			this->SetAnimState(eAnimState::StandLeft);
		//this->StopAnimation();
	}
}

