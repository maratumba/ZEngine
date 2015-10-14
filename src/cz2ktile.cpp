#include "cz2ktile.h"
#include <iostream>

int CZ2kTile::Draw()
{
	if(Sprite_)
		return Sprite_->DrawAt(GetPosX(), GetPosY());
	else
		std::cout << "Tile does not have a sprite attached" << std::endl;
	return 0;
}
