#ifndef __CDRAWABLE_H__
#define __CDRAWABLE_H__

class CDrawable
{
public:
 	CDrawable()	{;}
	virtual ~CDrawable() {;}

	void SetPos(int x, int y) {posx = x; posy = y;}
	int MoveRight(int dx) {posx += dx; return posx;}
	int MoveLeft(int dx)  {posx -= dx; return posx;}
	int MoveUp(int dy)    {posy += dy; return posy;}
	int MoveDown(int dy)  {posy -= dy; return posy;}
	void SetScale(int sx, int sy) {scalex = sx; scaley = sy;}

	virtual int Draw() = 0;

protected:
	int posx = 0;
	int posy = 0;
	int sizex = 0;
	int sizey = 0;
	int scalex = 1;
	int scaley = 1;
};

#endif

