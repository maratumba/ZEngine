#ifndef __CROOM_H__
#define __CROOM_H__

#include "cdrawable.h"
#include "rapidxml.hpp"
#include <string>
#include <vector>

class CSDLSprite;
class CCharacter;
class CSDLBlitter;

class CRoom: public CDrawable
{
public:
	CRoom(CSDLBlitter *blitter);
	virtual ~CRoom();
	int Draw() override;
	int ReadConfig(const std::string &file);
	int ReadConfig(const rapidxml::xml_node<> *node);
	
	CSDLSprite *Background_ = nullptr;
	CSDLSprite *Foreground_ = nullptr;
	
	std::vector<CCharacter *> characters_;

private:
	int ReadConfig_SpriteAnims(const rapidxml::xml_node<> *node, int &autoid);
	int ReadConfig_Characters(const rapidxml::xml_node<> *node, int &autoid);

	CSDLBlitter *Blitter_ = nullptr;
	std::vector<CSDLSprite *> Colliders_;
};

#endif //__CROOM_H__
