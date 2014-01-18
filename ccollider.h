#ifndef __CCOLLIDER_H__
#define __CCOLLIDER_H__

#include "cpolygon.h"

class CBlitter;

class CCollider
{
public:
	CCollider() {;}
	~CCollider() {;}

	void AddCollisionPolygon(CPolygon &poly);
	bool CollidesWith(CCollider &collider);

	void DumpCollisionPolygons();

protected:
	std::vector<CPolygon> CollisionPolygons_;
};

#endif

