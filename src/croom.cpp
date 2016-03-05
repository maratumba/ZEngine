#include "croom.h"
#include "csdlsprite.h"
#include "cspriteanim.h"
#include "ccharacter.h"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

#include <iostream>

CRoom::CRoom(CSDLBlitter* blitter):
	CDrawable(),
	Blitter_(blitter)
{
}

CRoom::~CRoom()
{
	for(auto &i : Colliders_)
	{
		delete i;
	}
	Colliders_.clear();
}

int CRoom::Draw()
{
	for(auto &i : Colliders_)
	{
		i->Draw();
	}
	for(const auto &i : Colliders_)
	{
		i->DrawCollisionPolygons(Blitter_);
	}
	return 0;
}

int CRoom::ReadConfig(const std::string &file)
{
	using namespace rapidxml;

	rapidxml::file<> f(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(f.data());

	xml_node<> *root = doc.first_node("room");
	if(!root)
		return 1;
	
	ReadConfig(root);
	return 0;
}

int CRoom::ReadConfig(const rapidxml::xml_node<> *node)
{
	using namespace rapidxml;
	int autoid = 1;

	std::cout << "Reading CRoom" << std::endl;

	// reading background

	xml_node<> *background = node->first_node("background");
	if(!background)
		return 1;

	xml_attribute<> *att;
	att = background->first_attribute("file");
	if(!att)
		return 1;
	
	Background_ = new CSDLSprite(autoid++, Blitter_);
	Background_->LoadImage(att->value());

	att = background->first_attribute("posX");
	if(!att)
		return 1;
	int posX = atoi(att->value());

	att = background->first_attribute("posY");
	if(!att)
		return 1;
	int posY = atoi(att->value());
	
	Background_->SetPos(posX, posY);
	Background_->ReadConfig(background);
	Colliders_.push_back(Background_);

	// reading CSpriteAnims
	ReadConfig_SpriteAnims(node, autoid);
	// reading CCharacters
	ReadConfig_Characters(node, autoid);
	
	// reading foreground

	xml_node<> *foreground = node->first_node("foreground");
	if(!foreground)
		return 1;

	att = foreground->first_attribute("file");
	if(!att)
		return 1;
	
	Foreground_ = new CSDLSprite(autoid++, Blitter_);
	Foreground_->LoadImage(att->value());

	att = foreground->first_attribute("posX");
	if(!att)
		return 1;
	posX = atoi(att->value());

	att = foreground->first_attribute("posY");
	if(!att)
		return 1;
	posY = atoi(att->value());
	
	Foreground_->SetPos(posX, posY);
	Foreground_->ReadConfig(foreground);
	Colliders_.push_back(Foreground_);

	std::cout << "Reading CRoom done" << std::endl;
	return 0;
}

int CRoom::ReadConfig_SpriteAnims(const rapidxml::xml_node<> *node, int &autoid)
{
	using namespace rapidxml;

	xml_node<> *anim = node->first_node("spriteanim");
	if(anim)
	{
		do
		{
			xml_attribute<> *att;

			att = anim->first_attribute("file");
			if(!att)
				return 1;

			char *safile = att->value();

			att = anim->first_attribute("posX");
			if(!att)
				return 1;

			int posX = atoi(att->value());

			att = anim->first_attribute("posY");
			if(!att)
				return 1;

			int posY = atoi(att->value());

			att = anim->first_attribute("firstFrame");
			if(!att)
				return 1;

			int firstFrame = atoi(att->value());

			att = anim->first_attribute("lastFrame");
			if(!att)
				return 1;

			int lastFrame = atoi(att->value());

			CSpriteAnim *sanim = new CSpriteAnim(autoid++, Blitter_);
			sanim->ReadConfig(safile);
			sanim->SetPos(posX, posY);
			sanim->SetActiveFrames(firstFrame, lastFrame);
			sanim->StartAnimation();

			Colliders_.push_back(sanim);

			anim = anim->next_sibling("spriteanim");
		}while(anim);
	}
	return 0;
}

int CRoom::ReadConfig_Characters(const rapidxml::xml_node<> *node, int &autoid)
{
	using namespace rapidxml;

	xml_node<> *charnode = node->first_node("character");
	if(charnode)
	{
		do
		{
			xml_attribute<> *att;
			att = charnode->first_attribute("file");
			if(!att)
				return 1;

			char *charfile = att->value();
			
			att = charnode->first_attribute("posX");
			if(!att)
				return 1;

			int posX = atoi(att->value());

			att = charnode->first_attribute("posY");
			if(!att)
				return 1;

			int posY = atoi(att->value());
			
			CCharacter *character = new CCharacter(autoid++, Blitter_, Colliders_);
			character->ReadConfig(charfile);
			character->SetPos(posX, posY);
			
			characters_.push_back(character);
			Colliders_.push_back(character);

			charnode = charnode->next_sibling("character");
		}while(charnode);
	}
	return 0;
}
