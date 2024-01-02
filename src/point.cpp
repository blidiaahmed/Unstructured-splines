#include "pch.h"
#include"point.h"

using namespace std;
// constructors
point::point() :point(0){}

point::point(int dim):dimension(dim),X(dim){}
point::point(vector<float>& x):X(x),dimension(x.size()) {}
point::point(vector<float>&& x) : X(x), dimension(x.size()) {}
//point::point(const point& pt) : X(pt.X), dimension(pt.dimension) {};
//point::point(const point&& pt) : X(pt.X), dimension(pt.dimension) {};
// getters
unsigned int point::getDimension() { return dimension; }
float		 point::getCoordinate(unsigned int i) { return X[i]; }
vector<float>&  point::getVector() { return X; }
float point::getNorm() { float L = 0;
for (int i=0; i<dimension;i++)
{
	L+=X[i]*X[i];
}
return sqrt(L);

}
//  setters 
void point::setCoordinate(unsigned int index, float fl){X[index] = fl;}

// operations
point operator * (float fl, point& pt1) 
{
	point pt2 = point(pt1.getDimension());
	for (int idx=0; idx<pt2.getDimension();idx++)
	{
		pt2.setCoordinate(idx, fl * pt1.getCoordinate(idx));
	}
	return pt2; 
}
point operator * (point& pt, float fl) { return fl * pt; }
point operator + (point& pt1, point& pt2)
{
	point pt3 = point(pt1.getDimension());
	for (int idx = 0; idx < pt3.getDimension();idx++)
	{
		pt3.setCoordinate(idx, pt1.getCoordinate(idx) + pt2.getCoordinate(idx));
	}
	return pt3;
}
point point::operator -() 
{
	point pt = point(getDimension());
	for (int idx = 0; idx < getDimension();idx++)
	{
		pt.setCoordinate(idx, - getCoordinate(idx));
	}
	return pt;
}
point operator -(point & pt1,point & pt2)
{
	point pt = point(pt1.getDimension());
	for (int idx = 0; idx < pt2.getDimension();idx++)
	{
		pt.setCoordinate(idx, pt1.getCoordinate(idx) -pt2.getCoordinate(idx));
	}
	return pt;
}
