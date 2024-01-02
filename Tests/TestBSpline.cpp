#include "pch.h"
#include"point.h"
#include"BSpline.h"
using namespace std;
TEST(BSpline, constructorsDimension1)
{
	unsigned int dimension=1;
	vector <unsigned int > degree(dimension);
	degree[0] = 3;

	BSpline BS{};
	EXPECT_EQ(BS.getDimension(), 1);
	EXPECT_EQ(BS.getDegree()[0], 3);
	//the default knots distribution correspond to bezier polynomials
	//eg. degree=3 means knots={0,0,0,0,1,1,1,1}
	EXPECT_EQ(BS.getKnots(0)[0], 0.);
	EXPECT_EQ(BS.getKnots(0)[4], 1.);


	BSpline BS0(dimension);
	EXPECT_EQ(BS0.getDimension(), 1);
	EXPECT_EQ(BS0.getDegree()[0], 3);
	EXPECT_EQ(BS0.getKnots(0)[0], 0.);
	EXPECT_EQ(BS0.getKnots(0)[4], 1.);

	BSpline BS1(dimension, degree);
	EXPECT_EQ(BS1.getDimension(), 1);
	EXPECT_EQ(BS1.getDegree()[0], 3);
	EXPECT_EQ(BS1.getKnots(0)[0],0.);
	EXPECT_EQ(BS1.getKnots(0)[4], 1.);
	EXPECT_EQ(BS1.getControlGridShape()[0], 4);

	vector < vector<float> > knots = { {0, 0, 0, 0,0.5, 1, 1, 1, 1} };
	vector<unsigned int> deg(1);
	deg[0] = 3;
	BSpline BS2 = BSpline(dimension, deg,knots);
	EXPECT_EQ(BS2.getKnots(0)[4], 0.5);
}

TEST(BSpline, constructorsDimension2nonKnots)
{
	unsigned int dimension = 2;
	vector <unsigned int > degree(dimension);
	degree[0] = 3;
	degree[1] = 5;
	
	BSpline BS1(dimension, degree);

	EXPECT_EQ(BS1.getDimension(), 2);
	EXPECT_EQ(BS1.getDegree()[1], 5);
	EXPECT_EQ(BS1.getKnots(0)[0], 0.);
	EXPECT_EQ(BS1.getKnots(1)[6], 1.);
	EXPECT_EQ(BS1.getControlGridShape()[0], 4);
	EXPECT_EQ(BS1.getControlGridShape()[1], 6);

}

TEST(BSpline, constructorsDimension2wihKnots)
{
	unsigned int dimension = 2;
	vector <unsigned int > degree(dimension);
	degree[0] = 2;
	degree[1] = 3;

	vector<vector<float>> knots(2);
	knots[0] = { 0,0,0,0.5,1.,1.,1. };
	knots[1] = { 0,0,0,0,0.3,0.7,1.,1.,1.,1. };
	BSpline BS1(dimension, degree, knots);

	EXPECT_EQ(BS1.getDimension(), 2);
	EXPECT_EQ(BS1.getDegree()[1], 3);
	EXPECT_EQ(BS1.getKnots(0)[0], 0.);
	EXPECT_EQ(BS1.getKnots(1)[6], 1.);
	EXPECT_EQ(BS1.getControlGridShape()[0], 4);
	EXPECT_EQ(BS1.getControlGridShape()[1], 6);
}