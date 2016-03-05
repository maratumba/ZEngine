#include "ccollider.h"
#include "cblitter.h"
#include <iostream>
#include <cfloat>
#include <cmath>

void CCollider::AddCollisionPolygon(CPolygon &poly)
{
	CollisionPolygons_.push_back(poly);
}

bool CCollider::CollidesWith(tPoint thisPos, const CCollider &otherCollider, tPoint otherPos) const
{
	for(const auto &poly1 : CollisionPolygons_)
	{
		for(const auto &poly2 : otherCollider.CollisionPolygons_)
		{
			bool rvl = PolygonCollision(thisPos, poly1, otherPos, poly2);
			if(rvl)
			{
				//std::cout << "collision: " << std::endl;
				//std::cout << "\tpoly this: " << thisPos.first << ", " << thisPos.second << std::endl;
				//DumpPolygon(poly1);
				//std::cout << "\tpoly other: " << otherPos.first << ", " << otherPos.second << std::endl;
				//DumpPolygon(poly2);
				
				return true;
			}
		}
	}
	return false;
}

void CCollider::DumpCollisionPolygons()
{
	for(const auto &poly : CollisionPolygons_)
	{
		DumpPolygon(poly);
	}
}

void CCollider::DumpPolygon(const CPolygon &poly)
{
		for(const auto &point : poly.Points_)
		{
			std::cout << "Point: " << point.first << ", " << point.second << std::endl;
		}
}

bool CCollider::PolygonCollision(tPoint posA, CPolygon polygonA, tPoint posB, CPolygon polygonB) const
{
	for(size_t ia = 0; ia < polygonA.Points_.size(); ++ia)
	{
		for(size_t ib = 0; ib < polygonB.Points_.size(); ++ib)
		{
			size_t ia2 = ia + 1;
			if(ia2 >= polygonA.Points_.size())
				ia2 = 0;

			size_t ib2 = ib + 1;
			if(ib2 >= polygonB.Points_.size())
				ib2 = 0;

			tPoint &pa1 = polygonA.Points_[ia];
			tPoint &pa2 = polygonA.Points_[ia2];

			tPoint &pb1 = polygonB.Points_[ib];
			tPoint &pb2 = polygonB.Points_[ib2];
			
			float ix = 0;
			float iy = 0;
			bool coll = GetLineIntersection(posA.first + pa1.first, posA.second + pa1.second,
																			posA.first + pa2.first, posA.second + pa2.second,
																			posB.first + pb1.first, posB.second + pb1.second,
																			posB.first + pb2.first, posB.second + pb2.second,
																			&ix, &iy);
			if(coll)
				return true;
		}
	}

	return false;
}

bool CCollider::GetLineIntersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y) const
{
	float s1_x;
	float s1_y;
	float s2_x;
	float s2_y;

	s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

	float s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i_x != NULL)
			*i_x = p0_x + (t * s1_x);
		if (i_y != NULL)
			*i_y = p0_y + (t * s1_y);
		return true;
	}

	return false; // No collision
}
/*
int CCollider::DotProduct(tPoint p1, tPoint p2)
{
	return p1.first*p2.first + p1.second*p2.second;
}
*/
/*
void CCollider::ProjectPolygon(tPoint axis, tPoint pos, const CPolygon &polygon, float &min, float &max)
{
	// To project a point on an axis use the dot product
	tPoint tmpPoint;
	tmpPoint.first = polygon.Points_[0].first + pos.first;
	tmpPoint.second = polygon.Points_[0].second + pos.second;
	
	float dotProduct = DotProduct(axis, tmpPoint);
	min = dotProduct;
	max = dotProduct;
	for (auto &p :  polygon.Points_)
	{
		tmpPoint.first = p.first + pos.first;
		tmpPoint.second = p.second + pos.second;
		
		dotProduct = DotProduct(axis, tmpPoint);
		if (dotProduct < min)
		{
			min = dotProduct;
		}
		else if (dotProduct > max)
		{
			max = dotProduct;
		}
	}
}
*/
/*
float CCollider::IntervalDistance(float minA, float maxA, float minB, float maxB)
{
	if (minA < minB)
	{
		return minB - maxA;
	}
	else
	{
		return minA - maxB;
	}
}
*/
/*
void CCollider::Normalize(tPoint &p)
{
	//Normalize the axis
	double len_v = sqrt(p.first * p.first + p.second * p.second);
	p.first /= len_v;
	p.second /= len_v;
}
*/
/*
bool CCollider::PolygonCollision(tPoint posA, CPolygon polygonA, tPoint posB, CPolygon polygonB)
{
	bool result = true;

	int edgeCountA = polygonA.Points_.size();
	int edgeCountB = polygonB.Points_.size();
	//float minIntervalDistance = FLT_MAX;
	tPoint translationAxis;
	tPoint edge;

	// Loop through all the edges of both polygons
	for (int edgeIndex = 0; edgeIndex < edgeCountA + edgeCountB; edgeIndex++)
	{
		int posX;
		int posY;
	
		if (edgeIndex < edgeCountA)
		{
			edge = polygonA.Points_[edgeIndex];
			posX = posA.first;
			posY = posA.second;
		}
		else
		{
			edge = polygonB.Points_[edgeIndex - edgeCountA];
			posX = posB.first;
			posY = posB.second;
		}

		// ===== 1. Find if the polygons are currently intersecting =====

		// Find the axis perpendicular to the current edge
		tPoint axis = {-(edge.second + posY), edge.first + posX};
		Normalize(axis);

		// Find the projection of the polygon on the current axis
		float minA = 0; float minB = 0; float maxA = 0; float maxB = 0;
		ProjectPolygon(axis, posA, polygonA, minA, maxA);
		ProjectPolygon(axis, posB, polygonB, minB, maxB);

		// Check if the polygon projections are currentlty intersecting
		if (IntervalDistance(minA, maxA, minB, maxB) > 0)
			result = false;
	}

	return result;
}
*/