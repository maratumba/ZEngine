#ifndef __CZ2KBOARD_H__
#define __CZ2KBOARD_H__

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
	int Value_;
	CDrawable *Sprite_;
};

#endif
