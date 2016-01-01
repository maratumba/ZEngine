#include "canimatormove.h"
#include <iostream>

void CAnimatorMove::Tick(int)
{
	if(Speed_ > 1)
	{
		int posX = Obj_->GetPosX();
		int posY = Obj_->GetPosY();
		int stepSizeX = (DestX_ - posX) / Speed_;
		int stepSizeY = (DestY_ - posY) / Speed_;
		Obj_->SetPos(posX + stepSizeX, posY + stepSizeY);
		std::cout << "moving to " << posX + stepSizeX << " " << posY + stepSizeY << std::endl;
		Speed_--;
	}
	else
		Obj_->SetPos(DestX_, DestY_);
}
