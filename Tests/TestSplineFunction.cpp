#include "pch.h"
#include"Example.h"
#include "splineFunctions.h"

using namespace std;
TEST(splineFunction, SplineCurve1D)
{
	vector< vector<float>> knotVector= vector< vector<float>>();
	knotVector.push_back(vector<float>{  0, 0, 0, 0, 0.5, 1, 1, 1, 1 });

	vector<unsigned int > degreeVector= vector< unsigned int >();
	degreeVector.push_back(3);

	int ParametricDimension = 1;

	spline sp(ParametricDimension, degreeVector,knotVector);

	sp.tensor1.push_back(point(vector<float>{ 1. }));
	sp.tensor1.push_back(point(vector<float>{ 2. }));
	sp.tensor1.push_back(point(vector<float>{ 1. }));
	sp.tensor1.push_back(point(vector<float>{ 1. }));
	sp.tensor1.push_back(point(vector<float>{ 2. }));
	point pt(sp.Evaluate(0.32));
	EXPECT_NEAR(pt.getNorm(), 1.53, 0.01);
}

TEST(splineFunction, SplineCurve3D)
{
	spline sp(3);
	sp.tensor1.push_back(point({ 1,1,1 }));
	sp.tensor1.push_back(point({ 1,1,0 }));
	sp.tensor1.push_back(point({ 1,0,1 }));
	sp.tensor1.push_back(point({ 0,1,1 }));
	point pt (sp.Evaluate(0.5));
	EXPECT_NEAR(pt.getNorm(), 1.2437, 0.01);
}

TEST(splineFunction, SplineCurve3D_KnotInsertion)
{
	spline sp(3);
	sp.tensor1 = vector<point>({ point({0,0,0}),point({1,0,0}),point({0,1,0}),point({1,1,1}) });
	vector<point> values;
	for (int i = 0;i < 11; i++)
	{
		values.push_back(sp.Evaluate(i / 10.0));
	}
	
	sp.knotInsert(0.5, 0);
	float error = 0;

	for (int i = 0;i < 11; i++)
	{
		point ptt = values[i];
		point pt = values[i] - sp.Evaluate(i / 10.0);
		error += pt.getNorm();
	}
	ASSERT_NEAR(error, 0, 0.001);
}


TEST(splineFunction, SplineSurface3D)
{
	spline sp(3);
	sp.BS= BSpline(2);
	tensor_example(sp.tensor2);
	point pt(sp.Evaluate({ 0,0}));
	point pt1(sp.Evaluate({ 0.5,0.5 }));
	point pt2(sp.Evaluate({ 0.75,0.25 }));
	EXPECT_NEAR(pt.getNorm(), 1., 0.01);
	EXPECT_NEAR(pt1.getNorm(), 2.34, 0.01);
	EXPECT_NEAR(pt2.getNorm(), 2.57, 0.01);
}



TEST(splineFunction, SplineSurface3D_KnotInsertion)
{

	spline sp(3);
	sp.BS = BSpline(2);

	tensor_example(sp.tensor2);
	vector<point> values;
	for (int j = 0;j < 11; j++)	
	for (int i = 0;i < 11; i++)
	{
		float I = i / 10.0;
		float J = j / 10.0;
		vector<float> vect({ I, J });
		values.push_back(sp.Evaluate(vect));
	}

	sp.knotInsert(0.5, 0);
	float error = 0;
	int cmp = 0;
	for (int j = 0;j < 11; j++)
	for (int i = 0;i < 11; i++)
	{
		float I = i / 10.0;
		float J = j / 10.0;
		vector<float> vect({ I, J });
		
		point pt = values[cmp++] - sp.Evaluate(vect);
		error += pt.getNorm();
		
	}
	ASSERT_NEAR(error, 0, 0.001);
}