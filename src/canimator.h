#ifndef __CANIMATOR_H__
#define __CANIMATOR_H__

#include "cdrawable.h"

class CAnimator
{
public:
	CAnimator(CDrawable *obj) {Obj_ = obj;}
	virtual~CAnimator() {;}

	virtual void Tick(int usec) = 0;

	void StartAnimation() {Running_ = true;}
	void StopAnimation() {Running_ = false;}
	bool isRunning() {return Running_;}
	
	CDrawable *GetDrawable() {return Obj_;}

protected:
	CDrawable *Obj_ = nullptr;
	bool Running_ = false;
};

#endif
