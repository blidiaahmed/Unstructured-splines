#include "pch.h"

#include"BSplines_Helper.h"
using namespace std;



TEST(BSplineDerivative, FindSpan)
{
	// This function does already exists, so it must be removed	
	int deg=2;
	float u= 5/2;
	vector <float >knots{ 0., 0, 0, 1, 2, 3, 4, 4, 5, 5, 5 };

	EXPECT_EQ(FindSpan( deg, u, knots),4);


}

TEST(BSplineDer, ComputeNbBasis)
{
	// This function does already exists, so it must be removed
	int deg = 2;

	vector <float > knots{ 0., 0, 0, 1, 2, 3, 4, 4, 5, 5, 5 };
	EXPECT_EQ(ComputNumberOfBasisElts(deg, knots), 8);
	vector <float > knots2{ 0., 0, 0, 5, 5, 5 };
	EXPECT_EQ(ComputNumberOfBasisElts(deg, knots2), 3);

}


TEST(BSplines, CoxDeBoor)
{

	int deg = 3;
	float u = 0;
	vector <float > knots{ 0., 0, 0,0,1,1,1,1. };
	float result = coxDeBoor(3, 0, u, knots);
	EXPECT_EQ(1, result);

	result = coxDeBoor(4, 0, 0., knots);
	EXPECT_EQ(0, result);

	vector <float > knots2{ 0., 0, 0,1,1,1. };
	u = 0.5;
	result = coxDeBoor(1, 2, u, knots2);
	EXPECT_EQ(0.5, result);

	result = coxDeBoor(0, 2, u, knots2);
	EXPECT_EQ(0.25, result);

	vector<float >knots3{ 0, 0, 0, 1, 2, 3, 4, 4, 5, 5, 5 };
	result = coxDeBoor(1, 2, u, knots3);
	EXPECT_EQ(0.625, result);


	result = coxDeBoor(0, 1, u, knots3);
	EXPECT_EQ(0., result);

	result = coxDeBoor(1, 1, u, knots3);
	EXPECT_EQ(0.5, result);
}

TEST(BSplineDer, ComputingDerivative)
{
	int deg = 2;

	vector <float > knots{ 0., 0, 0, 1, 2, 3, 4, 4, 5, 5, 5 };
	float result = bsplineDerivative(4,deg, 2.5, knots);
	EXPECT_EQ(0.5, result);

	result = bsplineDerivative(7, deg, 4.5, knots);
	EXPECT_EQ(1, result);

	result = bsplineDerivative(2, deg, 0.5, knots);
	EXPECT_EQ(0.5, result);


	result = bsplineDerivative(0, deg, 0.25, knots);
	EXPECT_EQ(-1.5, result);

	result = bsplineDerivative(0, deg, 0.5, knots);
	EXPECT_EQ(-1, result);


	vector <float > knots2{ 0., 0, 0, 0, 2,4,6, 8,8,8, 8};
	result = bsplineDerivative(3, 3,4., knots);

	EXPECT_EQ(0, result);

}

