#ifndef __CCOLLIDER_H__
#define __CCOLLIDER_H__

#include "cpolygon.h"

class CCollider
{
public:
	CCollider() {;}
	~CCollider() {;}

	bool CollidesWith(CCollider &collider);

private:
	std::vector<CPolygon> Polygons;
};

#endif

