#ifndef __CCOLLIDER_H__
#define __CCOLLIDER_H__

#include "cpolygon.h"

class CBlitter;

class CCollider
{
public:
	CCollider(int id):Id_(id) {;}
	~CCollider() {;}

	int GetId() {return Id_;}

	void AddCollisionPolygon(CPolygon &poly);
	bool CollidesWith(tPoint thisPos, CCollider &otherCollider, tPoint otherPos);

	void DumpCollisionPolygons();

protected:
	int Id_;
	std::vector<CPolygon> CollisionPolygons_;

	int DotProduct(tPoint p1, tPoint p2);
	// Calculate the projection of a polygon on an axis
	// and returns it as a [min, max] interval
	void ProjectPolygon(tPoint axis, tPoint posA, const CPolygon &polygon, float &min, float &max);
	// Calculate the distance between [minA, maxA] and [minB, maxB]
	// The distance will be negative if the intervals overlap
	float IntervalDistance(float minA, float maxA, float minB, float maxB);
	void Normalize(tPoint &p);
	// Check if polygon A is going to collide with polygon B.
	// The last parameter is the *relative* velocity 
	// of the polygons (i.e. velocityA - velocityB)
	bool PolygonCollision(tPoint posA, CPolygon polygonA, tPoint posB, CPolygon polygonB);
};

#endif
