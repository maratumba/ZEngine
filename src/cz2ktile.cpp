#include "cz2ktile.h"

int CZ2kTile::Draw()
{
	if(Sprite_)
		return Sprite_->Draw();
	return 0;
}
