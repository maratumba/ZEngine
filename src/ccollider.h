#ifndef __CCOLLIDER_H__
#define __CCOLLIDER_H__

#include "cpolygon.h"

class CBlitter;

class CCollider
{
public:
	CCollider(int id):Id_(id) {;}
	~CCollider() {;}

	int GetId() const {return Id_;}

	void AddCollisionPolygon(CPolygon &poly);
	bool CollidesWith(tPoint thisPos, const CCollider &otherCollider, tPoint otherPos) const;

	void DumpCollisionPolygons();

protected:
	int Id_;
	std::vector<CPolygon> CollisionPolygons_;

	void DumpPolygon(const CPolygon &poly);

	bool PolygonCollision(tPoint posA, CPolygon polygonA, tPoint posB, CPolygon polygonB) const;

private:
	// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
	// intersect the intersection point may be stored in the floats i_x and i_y.
	bool GetLineIntersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y) const;

	
	//int DotProduct(tPoint p1, tPoint p2);
	// Calculate the projection of a polygon on an axis
	// and returns it as a [min, max] interval
	//void ProjectPolygon(tPoint axis, tPoint posA, const CPolygon &polygon, float &min, float &max);
	// Calculate the distance between [minA, maxA] and [minB, maxB]
	// The distance will be negative if the intervals overlap
	//float IntervalDistance(float minA, float maxA, float minB, float maxB);
	//void Normalize(tPoint &p);
	// Check if polygon A is going to collide with polygon B.
	// The last parameter is the *relative* velocity 
	// of the polygons (i.e. velocityA - velocityB)
	//bool PolygonCollision(tPoint posA, CPolygon polygonA, tPoint posB, CPolygon polygonB);
};

#endif
