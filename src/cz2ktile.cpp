#include "cz2ktile.h"
#include "canimatormove.h"
#include <iostream>

int CZ2kTile::Draw()
{
	if(Sprite_)
		return Sprite_->DrawAt(GetPosX(), GetPosY());
	else
		std::cout << "Tile does not have a sprite attached" << std::endl;
	return 0;
}

void CZ2kTile::Tick(int usec)
{
	if(Mover_)
		Mover_->Tick(usec);
}

void CZ2kTile::MoveTo(int /*x*/, int /*y*/)
{
/*	if(Sprite_)
	{
		if(Mover_)
			delete Mover_;
		Mover_ = new CAnimatorMove(this, x, y, 100);
		Mover_->StartAnimation();
	}
*/
}
