#ifndef __CZ2KTILE_H__
#define __CZ2KTILE_H__

#include "cdrawable.h"

class CAnimatorMove;

class CZ2kTile: public CDrawable
{
public:
	CZ2kTile(): CDrawable() {;}
	virtual ~CZ2kTile() {;}

	virtual int Draw() override;
	void Tick(int usec);

	int GetValue() {return Value_;}
	void SetValue(int v, CDrawable *sprite) {Value_ = v; Sprite_ = sprite;}

	void MoveTo(int x, int y);

private:
	int Value_ = 0;
	CDrawable *Sprite_ = nullptr;
	CAnimatorMove *Mover_ = nullptr;
};

#endif
