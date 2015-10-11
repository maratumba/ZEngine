#include "canimatorscale.h"

#include <iostream>

void CAnimatorScale::Tick(int usec __attribute__((__unused__)))
{
	if(Running_)
	{
		double s = Scale_[ScalePos_];
		
		if(obj_)
			obj_->SetScale(s, s);
		
		ScalePos_ += 0.3;
		if(ScalePos_ >= Scale_.size())
			Running_ = false;
	}
}
