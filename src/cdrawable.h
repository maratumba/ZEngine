#ifndef __CDRAWABLE_H__
#define __CDRAWABLE_H__

class CDrawable
{
public:
	enum class AnchorPos
	{
		TOP_LEFT,
		CENTER
	};
	
 	CDrawable() {;}
	virtual ~CDrawable() {;}

	void SetPos(int x, int y) {PosX_ = x; PosY_ = y;}
	int GetPosX() const {return PosX_;}
	int GetPosY() const {return PosY_;}

	int MoveRight(int dx) {PosX_ += dx; return PosX_;}
	int MoveLeft(int dx)  {PosX_ -= dx; return PosX_;}
	int MoveUp(int dy)    {PosY_ -= dy; return PosY_;}
	int MoveDown(int dy)  {PosY_ += dy; return PosY_;}

	void SetScale(double sx, double sy) {ScaleX_ = sx; ScaleY_ = sy;}
	double GetScaleX() const {return ScaleX_;}
	double GetScaleY() const {return ScaleY_;}

	int GetSizeX() const {return SizeX_;}
	int GetSizeY() const {return SizeY_;}

	void SetAnchorPos(AnchorPos apos) {AnchorPos_ = apos;}
	AnchorPos GetAnchorPos() {return AnchorPos_;}
	
	virtual int Draw() = 0;
	int DrawAt(int x, int y) {SetPos(x, y); return Draw();}

protected:
	AnchorPos AnchorPos_ = AnchorPos::TOP_LEFT;
	int SizeX_ = 0;
	int SizeY_ = 0;

private:
	double ScaleX_ = 1;
	double ScaleY_ = 1;
	int PosX_ = 0;
	int PosY_ = 0;
};

#endif
