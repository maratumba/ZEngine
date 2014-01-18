#include "ccollider.h"
#include "cblitter.h"
#include <iostream>

void CCollider::AddCollisionPolygon(CPolygon &poly)
{
	CollisionPolygons_.push_back(poly);
}

bool CCollider::CollidesWith(CCollider &collider)
{
	return false;
}

void CCollider::DumpCollisionPolygons()
{
	for(auto &poly : CollisionPolygons_)
	{
		for(auto &point : poly.Points_)
		{
			std::cout << "Point: " << point.first << ", " << point.second << std::endl;
		}
	}
}

