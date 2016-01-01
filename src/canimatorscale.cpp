#include "canimatorscale.h"

#include <iostream>

void CAnimatorScale::Tick(int)
{
	if(Running_)
	{
		double s = Scale_[ScalePos_];
		
		if(Obj_)
			Obj_->SetScale(s, s);
		
		ScalePos_ += 0.3;
		if(ScalePos_ >= Scale_.size())
			Running_ = false;
	}
}
