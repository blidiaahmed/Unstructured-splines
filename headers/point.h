#pragma once
using namespace std;
class point
{

public:
	unsigned int dimension;
	vector<float> X;
	point();
	//point(const point & pt);
	//point(const point && pt);

	point(int dim);
	point(vector<float>& x);
	
	point(vector<float>&& x);
	unsigned int getDimension();
	float getCoordinate(unsigned int);
	vector<float>& getVector();
	void setCoordinate(unsigned int, float);
	float getNorm();
	point operator -() ;
};
point operator * (float fl, point& pt);
point operator * (point& pt, float fl);
point operator + (point& pt1, point& pt2);
point operator -(point& pt1, point& pt2);
