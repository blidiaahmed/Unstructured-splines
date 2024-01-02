#include "pch.h"
#include "BSpline.h"
BSpline::BSpline():ParametricDimension(1)
{
	
	degree= vector<unsigned int>(ParametricDimension);
	degree[0] = 3;
	vector<vector<float>> knts = multivariatePolynomialKnotDistribution(ParametricDimension, degree);
	knot = knts;
	computeControlGridShape();
}
BSpline::BSpline(unsigned __int8 dim):ParametricDimension(dim)
{
	degree = vector<unsigned int>(ParametricDimension);
	for (int i = 0; i < ParametricDimension;i++)
	{
		degree[i] = 3;
	}
	
	vector<vector<float>> knts = multivariatePolynomialKnotDistribution(ParametricDimension, degree);
	knot = knts;
	computeControlGridShape();
}
BSpline::BSpline(unsigned int dim, vector<unsigned int>& deg)
:ParametricDimension(dim), degree(deg)
{
	vector<vector<float>> knts = multivariatePolynomialKnotDistribution(dim,deg);
	knot = knts;
	computeControlGridShape();
}
BSpline::BSpline(unsigned int dim, vector<unsigned int>& deg,
	vector<vector<float>> knts)
	:ParametricDimension(dim), degree(deg), knot(knts) {computeControlGridShape();}
vector<float> BSpline::getKnots(unsigned int axIndex){return knot[axIndex];}
unsigned int BSpline::getDimension(){return ParametricDimension;}
vector <unsigned int > BSpline::getDegree() { return degree; }
vector<unsigned int> BSpline::getControlGridShape() { return controlGridShape; }
void BSpline::setDimension(unsigned int dim) { ParametricDimension = dim; }
void BSpline::computeControlGridShape() 
{
	controlGridShape = vector<unsigned int >(ParametricDimension);
	for (int index = 0; index < ParametricDimension;index++)
	{
		controlGridShape[index] = -degree[index] -1 + knot[index].size();
	}
}
vector<vector<float>> BSpline::multivariatePolynomialKnotDistribution(
	unsigned int dim, vector<unsigned int>& deg)
{
	vector<vector<float>> knts(dim);
	int knotsNumber;
	for (int i = 0; i < dim; i++)
	{
		knotsNumber = 2 * deg[i] + 2;
		vector<float> knt(knotsNumber);
		knts[i] = UnivariatePolynomialKnotDistribution(deg[i], knt);
	}
	return knts;
}
vector<float>& UnivariatePolynomialKnotDistribution(int deg, vector<float> & knt)
{
	int kntNb=2*deg+2	;
	for (int j = 0; j < kntNb;j++)
	{
		if (j <= deg ) { knt[j] = 0; }
		else              { knt[j] = 1; }
	}
	return knt;
}
