#include "pch.h"
#include"Example.h"
#include"Maths.h"
#include"SplinesDerivatives.h"
using namespace std;

TEST(SplineCurveDerivatives, SplineDerivation)
{
	// evaluate a SPLINE  FUNCTION
	int deg = 3;
	vector<float> knots = { 0,0,0,0,1,1,1,1 };
	vector < point> ControlPoints = { point(vector<float>{1.}),point(vector<float>{2.}),point(vector<float>{3.}),point(vector<float>{4.}) };


	float u = 0.25;
	float h = 0.0001;
	
	int nbKnots = 7;
	point pt((1/h)*(evaluateSpline(u+h, knots, nbKnots, ControlPoints, deg)-
		evaluateSpline(u, knots, nbKnots, ControlPoints, deg)));
	ASSERT_NEAR(
		evaluateSplineDerivative(u, knots,ControlPoints, deg).getCoordinate(0),
		pt.getCoordinate(0),0.01);


	u = 0.55;
	h = 0.0001;

	
	point pt1((1 / h) * (evaluateSpline(u + h, knots, nbKnots, ControlPoints, deg) -
		evaluateSpline(u, knots, nbKnots, ControlPoints, deg)));
	ASSERT_NEAR(
		evaluateSplineDerivative(u, knots, ControlPoints, deg).getCoordinate(0),
		pt1.getCoordinate(0), 0.01);
	
}


TEST(SplineCurveDerivatives, TensorSplineDerivation)
{
	
	vector<vector<float>> t{ vector<float>{0,0,0,0,1,1,1,1},vector<float>{0,0,0,0,1,1,1,1} };
	vector<int> m{ 7,7 };
	vector<vector<point>> c;
	tensor_example2(c);
	vector< int > p{ 3,3 };

	float u = 0.25;
	float v = 0.5;
	float h = 0.0001;
	
	vector<float> x1{ u,v };
	vector<float> x2{ u+h,v };

	point pt(evaluateTensorSplineDerivative_FirstAxe(x1, t, m, c, p));
	point pt1(evaluateTensorSpline(x2, t, m, c, p)- evaluateTensorSpline(x1, t, m, c, p));
	pt1 = pt1 * (1 / h);
	ASSERT_NEAR(pt.getCoordinate(0), pt1.getCoordinate(0), 0.01);
	ASSERT_NEAR(pt.getCoordinate(1), pt1.getCoordinate(1), 0.01);
	ASSERT_NEAR(pt.getCoordinate(2), pt1.getCoordinate(2), 0.01);

}