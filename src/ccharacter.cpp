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
	return Collides({this->GetPosX(), this->GetPosY()});
}

bool CCharacter::Collides(tPoint thisPos)
{
	ActiveColliders_.clear();
	
	for(const auto &coll : Colliders_)
	{
		if(GetId() == coll->GetId())
			continue;

		tPoint otherPos(coll->GetPosX(), coll->GetPosY());
		
		bool rvl = CollidesWith(thisPos, *coll, otherPos);
		if(rvl)
			ActiveColliders_.push_back(coll);
	}
	if(ActiveColliders_.size())
	{
		//std::cout << "This " << GetId() << " collides with ";
		//for(const auto &c: ActiveColliders_)
		//	std::cout << c->GetId() << " ";
		//std::cout << std::endl;
		return true;
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
	if(keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_UP])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x+1, y-1}))
		{
			x += 1;
			y -= 1;
		}

		SetPos(x, y);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_DOWN])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x+1, y+1}))
		{
			x += 1;
			y += 1;
		}

		SetPos(x, y);
		this->SetAnimState(eAnimState::WalkRight);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_UP])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x-1, y-1}))
		{
			x -= 1;
			y -= 1;
		}

		SetPos(x, y);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_LEFT] && keys[SDL_SCANCODE_DOWN])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x-1, y+1}))
		{
			x -= 1;
			y += 1;
		}

		SetPos(x, y);
		this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_RIGHT])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x+2, y}))
			x += 2;

		SetPos(x, y);
		SetAnimState(eAnimState::WalkRight);
		StartAnimation();
	}
	else if(keys[SDL_SCANCODE_LEFT])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x-2, y}))
			x -= 2;

		SetPos(x, y);
		SetAnimState(eAnimState::WalkLeft);
		StartAnimation();
	}
	else if(keys[SDL_SCANCODE_UP])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x, y-2}))
			y -= 2;

		SetPos(x, y);
		if(State_ == eAnimState::StandRight)
			this->SetAnimState(eAnimState::WalkRight);
		if(State_ == eAnimState::StandLeft)
			this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else if(keys[SDL_SCANCODE_DOWN])
	{
		int x = GetPosX();
		int y = GetPosY();
		
		if(!Collides({x, y+2}))
			y += 2;

		SetPos(x, y);
		if(State_ == eAnimState::StandRight)
			this->SetAnimState(eAnimState::WalkRight);
		if(State_ == eAnimState::StandLeft)
			this->SetAnimState(eAnimState::WalkLeft);
		this->StartAnimation();
	}
	else
	{
		if(State_ == eAnimState::WalkRight)
			this->SetAnimState(eAnimState::StandRight);
		if(State_ == eAnimState::WalkLeft)
			this->SetAnimState(eAnimState::StandLeft);
	}
}

