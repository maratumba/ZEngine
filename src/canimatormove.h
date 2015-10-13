#ifndef __CANIMATORMOVE_H__
#define __CANIMATORMOVE_H__

#include "canimator.h"
#include <vector>

class CAnimatorMove: public CAnimator
{
public:
	CAnimatorMove(CDrawable* obj, int destX, int destY, int speed)
		: CAnimator(obj)
		, DestX_(destX)
		, DestY_(destY)
		, Speed_(speed)
		{;}
	virtual ~CAnimatorMove() {;}

	virtual void Tick(int usec) override;

private:
	int DestX_;
	int DestY_;
	int Speed_;
};

#endif
