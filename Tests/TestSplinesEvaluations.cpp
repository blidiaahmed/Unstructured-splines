#include "pch.h"
#include"Example.h"
#include"Maths.h"
using namespace std;


TEST(TestMaths, FactorialSpecialValues)
{
	int n = 0;
	ASSERT_EQ(factorial(n), 1);
}

TEST(TestMaths,BinomialSpecialValues)
{
	int n = 1, i = 0;
	ASSERT_EQ(binomial(i, n), 1);
}

TEST(TestMaths, SelectIntervalIndex)
{
	vector <float> t = { 1,1,1,2,2,3,3 };

	float x = 1;
	ASSERT_EQ(SelectIntervalIndex(x, t), 2);
	x = 2.5;
	int k = SelectIntervalIndex(x, t);
	ASSERT_EQ(k, 4);
	x = 2;
	ASSERT_EQ(SelectIntervalIndex(x, t), 4);
}


TEST(TestMaths, SplineBasicEvaluationFunction)
{
	// evaluate a SPLINE  FUNCTION
	vector<float> t = { 0,0,0,0,1,1,1,1 };
	vector < point> c = { point(vector<float>{1.}),point(vector<float>{2.}),point(vector<float>{3.}),point(vector<float>{4.}) };


	int p = 3;
	int k = 3;
	int m = 7;
	ASSERT_EQ(evaluateSpline(0., t, m, c,p).getCoordinate(0), 1);
	
	ASSERT_EQ(evaluateSpline(1., t, m, c, p).getCoordinate(0), 4);
	
	ASSERT_NE(evaluateSpline(0.5, t, m, c, p).getCoordinate(0), 1);
	
	
	c = { point(vector<float>{1.}),point(vector<float>{0.}),point(vector<float>{0.}),point(vector<float>{0.}) };
	for (int i = 0; i < 10;i++)
	{
		float x = (float)i / 10;
		ASSERT_NEAR(evaluateSpline(x, t, m, c, p).getCoordinate(0) - binomial(0, p) * pow((1 - x), (p)), 0, 0.01);
	}
		
	c = { point(vector<float>{0.}),point(vector<float>{0.}),point(vector<float>{0.}),point(vector<float>{1.}) };


	for (int i = 0; i < 10;i++)
	{
		
		float x = (float)i / 10;
		float f = binomial(0, p) * pow((x), (p));
		point pt = point(vector<float>{f});
		point ptp= evaluateSpline(x, t, m, c, p) - pt;
		float dist = ptp.getNorm();
		ASSERT_NEAR(dist, 0, 0.01);
	}
	
}


TEST(TestMaths, 3dSplineSurface)
{
	vector<float> x{ 0,0 };
	vector<vector<float>> t{ vector<float>{0,0,0,0,1,1,1,1},vector<float>{0,0,0,0,1,1,1,1} };
	vector<int> m{ 7,7 };
	vector<vector<point>> c;
	tensor_example(c);
	vector< int > p{ 3,3 };
	point pt(evaluateTensorSpline(x, t, m, c, p));
	ASSERT_NEAR(pt.getNorm(), 1, 0.1);
}