#include "cpolygon.h"

void CPolygon::AddPoint(tPoint &p)
{
	Points.push_back(p);
}

bool CPolygon::CollidesWith(CPolygon &poly)
{
	return true;
}

