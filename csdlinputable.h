#ifndef __CSDLINPUTABLE_H__
#define __CSDLINPUTABLE_H__

class CSDLInputable
{
public:
	CSDLInputable() {;}
	~CSDLInputable() {;}

	virtual void UpdateKeybState(unsigned char *keys) = 0;
};


#endif

