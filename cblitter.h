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
private:
};

#endif

