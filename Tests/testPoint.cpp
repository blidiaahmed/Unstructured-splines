#include"pch.h"
#include"point.h"

TEST(point, constructorsAndBasicFunctions)
{
	unsigned int dim = 3;
	point pt1=point();
	point pt2(dim);
	vector<float> X = { 1.0,1.2 };
	point pt3(move(X));
	EXPECT_EQ(pt1.getDimension(), 0);
	EXPECT_EQ(pt2.getDimension(), dim);
	EXPECT_EQ(pt3.getDimension(), 2);
	EXPECT_EQ(floor((pt3.getCoordinate(1)- 1.2)/100)*100,0);
	EXPECT_EQ(floor((pt3.getVector()[0]- 1.0)/100)*100,0);
	pt3.setCoordinate(1,2.5);
	EXPECT_EQ(floor((pt3.getCoordinate(1) - 2.5) * 10)/10, 0);
}




TEST(point, operations)
{
	vector <float> X = { 1.,2.,3. };
	point pt1 = point(move(X)), pt2 = point(move(X));
	float fl=0.5;
	EXPECT_EQ((pt1 * fl).getCoordinate(1), 1.);
	EXPECT_EQ((pt1 * fl).getCoordinate(0), 0.5);
	EXPECT_EQ((pt1 + pt2).getCoordinate(2), 6.);
	EXPECT_EQ((-pt2).getCoordinate(2), -3.);
	EXPECT_EQ((pt1 - pt2).getCoordinate(2), 0.);
	pt1 = pt1 - pt2;
	EXPECT_EQ((pt1 ).getCoordinate(2), 0.);
	// Testing norm
	point pt3({ 0,0,0 });
	EXPECT_NEAR(pt3.getNorm(), 0, 0.01);
	point pt4({ 1,-1,0 });
	EXPECT_NEAR(pt4.getNorm(), sqrt(2), 0.01);
	point pt5({ 1,2,3 });
	EXPECT_NEAR(pt5.getNorm(), sqrt(14), 0.01);
}