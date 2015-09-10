#ifndef __CSDLINPUTSINK_H__
#define __CSDLINPUTSINK_H__

class CSDLInputSink
{
public:
	CSDLInputSink() {;}
	virtual ~CSDLInputSink() {;}

	virtual void UpdateKeybState(const unsigned char *keys) = 0;
};


#endif

