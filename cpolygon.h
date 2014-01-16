#ifndef __CPOLYGON_H__
#define __CPOLYGON_H__

#include <utility>
#include <vector>

typedef std::pair<int, int> tPoint;

class CPolygon
{
public:
	CPolygon() {;}
	~CPolygon() {;}

	void AddPoint(tPoint &p);
	bool CollidesWith(CPolygon &poly);

private:
	std::vector<tPoint> Points;
};

#endif

