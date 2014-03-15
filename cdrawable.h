#ifndef __CDRAWABLE_H__
#define __CDRAWABLE_H__

class CDrawable
{
public:
 	CDrawable() {;}
	virtual ~CDrawable() {;}

	void SetPos(int x, int y) {PosX_ = x; PosY_ = y;}
	int GetPosX() {return PosX_;}
	int GetPosY() {return PosY_;}

	int MoveRight(int dx) {PosX_ += dx; return PosX_;}
	int MoveLeft(int dx)  {PosX_ -= dx; return PosX_;}
	int MoveUp(int dy)    {PosY_ -= dy; return PosY_;}
	int MoveDown(int dy)  {PosY_ += dy; return PosY_;}

	void SetScale(int sx, int sy) {ScaleX_ = sx; ScaleY_ = sy;}
	int GetScaleX() {return ScaleX_;}
	int GetScaleY() {return ScaleY_;}

	int GetSizeX() {return SizeX_;}
	int GetSizeY() {return SizeY_;}

	virtual int Draw() = 0;

protected:
	int SizeX_ = 0;
	int SizeY_ = 0;

private:
	int ScaleX_ = 1;
	int ScaleY_ = 1;
	int PosX_ = 0;
	int PosY_ = 0;
};

#endif

