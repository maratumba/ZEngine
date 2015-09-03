#ifndef __CBLITTER_H__
#define __CBLITTER_H__

class CBlitter
{
public:
	CBlitter() {};
	virtual ~CBlitter() {};

	virtual int Init(int width, int height, int bpp) = 0;
	virtual int Clear() = 0;
	virtual int Draw() = 0;
	virtual void DrawLine(int x1, int y1, int x2, int y2) = 0;
	virtual void SetDrawColor(int r, int g, int b, int a) = 0;

	void SetOffset(int x, int y) {ViewOffsetX_ = x; ViewOffsetY_ = y;}
	void MoveOffset(int dx, int dy) {ViewOffsetX_ += dx; ViewOffsetY_ += dy;}
	int GetOffsetX() {return ViewOffsetX_;}
	int GetOffsetY() {return ViewOffsetY_;}
	int GetWidth() {return ViewWidth_;}
	int GetHeight() {return ViewHeight_;}

private:
	int ViewOffsetX_ = 0;
	int ViewOffsetY_ = 0;
	
protected:
	int ViewWidth_ = 0;
	int ViewHeight_ = 0;
	int ViewBpp_ = 0;
};

#endif

