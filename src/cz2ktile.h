#ifndef __CZ2KTILE_H__
#define __CZ2KTILE_H__

#include "cdrawable.h"

class CDrawable;

class CZ2kTile: public CDrawable
{
public:
	CZ2kTile(): CDrawable() {;}
	virtual ~CZ2kTile() {;}

	virtual int Draw();

	int GetValue() {return Value_;}
	void SetValue(int v, CDrawable *sprite) {Value_ = v; Sprite_ = sprite;}

private:
	int Value_ = 0;
	CDrawable *Sprite_ = nullptr;
};

#endif
