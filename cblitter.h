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
private:
};

#endif

