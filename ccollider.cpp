#include "ccollider.h"
#include "cblitter.h"
#include <iostream>
#include <cfloat>
#include <cmath>

void CCollider::AddCollisionPolygon(CPolygon &poly)
{
	CollisionPolygons_.push_back(poly);
}

bool CCollider::CollidesWith(tPoint thisPos, CCollider &otherCollider, tPoint otherPos)
{
	for(auto poly1 : CollisionPolygons_)
	{
		for(auto poly2 : otherCollider.CollisionPolygons_)
		{
			bool rvl = PolygonCollision(thisPos, poly1, otherPos, poly2);
			if(rvl)
			{/*
				std::cout << "collision: " << std::endl;
				std::cout << "\tpoly this: " << thisPos.first << ", " << thisPos.second << std::endl;
				DumpPolygon(poly1);
				std::cout << "\tpoly other: " << otherPos.first << ", " << otherPos.second << std::endl;
				DumpPolygon(poly2);
				*/
				return rvl;
			}
		}
	}
	return false;
}

void CCollider::DumpCollisionPolygons()
{
	for(auto &poly : CollisionPolygons_)
	{
		DumpPolygon(poly);
	}
}

void CCollider::DumpPolygon(const CPolygon &poly)
{
		for(auto &point : poly.Points_)
		{
			std::cout << "Point: " << point.first << ", " << point.second << std::endl;
		}
}

int CCollider::DotProduct(tPoint p1, tPoint p2)
{
	return p1.first*p2.first + p1.second*p2.second;
}

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

void CCollider::Normalize(tPoint &p)
{
	//Normalize the axis
	double len_v = sqrt(p.first * p.first + p.second * p.second);
	p.first /= len_v;
	p.second /= len_v;
}

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
