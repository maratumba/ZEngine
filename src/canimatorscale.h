#ifndef __CANIMATORSCALE_H__
#define __CANIMATORSCALE_H__

#include "canimator.h"
#include <vector>

class CAnimatorScale: public CAnimator
{
public:
	CAnimatorScale(CDrawable* obj, std::vector<double> scale): CAnimator(obj), Scale_(scale) {;}
	virtual ~CAnimatorScale() {;}

	virtual void Tick(int usec) override;

private:
	std::vector<double> Scale_;
	double ScalePos_ = 0;
};

#endif
