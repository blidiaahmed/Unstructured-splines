#include"pch.h"
#include"Example.h"
#include"knotInsertion_Splines.h"
#include"splineFunctions.h"


TEST(TestkontInsertion_spline, UnchangebilityOfTheCurve)
{
	spline sp(3);
	sp.tensor1 = vector<point>({ point({0,0,0}),point({1,0,0}),point({0,1,0}),point({1,1,1}) });
	vector<point> values;
	for (int i = 0;i < 11; i++)
	{
		values.push_back(sp.Evaluate(i / 10.0));
	}
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.5);
	ASSERT_EQ(sp.tensor1.size(),5 );
	float error=0;

	for (int i = 0;i < 11; i++)
	{
		point ptt = values[i];
		point pt =values[i]-sp.Evaluate(i / 10.0);
		error += pt.getNorm();
	}
	ASSERT_NEAR(error, 0,0.001);
}

TEST(TestkontInsertion_spline, UnchangebilityOfTheSurface_AxeOne)
{
	spline sp(3);
	sp.BS = BSpline(2);
	tensor_example(sp.tensor2);

	vector<point> values;
	for (int i = 0;i < 11; i++)
		for (int j = 0;j < 11; j++)
		{
			vector<float> vect;
			vect.push_back((float)i / 10.0);
			vect.push_back((float)j / 10.0);
			values.push_back(sp.Evaluate(vect));
		}
	int axeOfInsertion = 0;
	vector<vector<point>>& controlePoints = sp.tensor2;
	vector< vector<float>>& knots = sp.BS.knot;
	int degree = sp.BS.degree[axeOfInsertion];
	float knotToInsert = 0.5;
	knotInsertion::knotInsert(controlePoints,
		knots, degree, knotToInsert, 
		axeOfInsertion);
	ASSERT_EQ(controlePoints.size(), 5);
	// evaluation test
	int counter = 0;
	for (int i = 0;i < 11; i++)
		for (int j = 0;j < 11; j++)
		{
			vector<float> vect;
			vect.push_back((float)i / 10.0);
			vect.push_back((float)j / 10.0);
			point pt = sp.Evaluate(vect) - values[counter];
			EXPECT_NEAR(pt.getNorm(), 0, 0.01);
			counter++;
		}
	// test knots
}

TEST(TestkontInsertion_spline, UnchangebilityOfTheSurface_AxeTwo)
{
	spline sp(3);
	sp.BS = BSpline(2);
	tensor_example(sp.tensor2);
	
	vector<point> values;
	for (int i = 0;i < 11; i++)
		for (int j = 0;j < 11; j++)
		{
			vector<float> vect;
			vect.push_back((float)i / 10.0);
			vect.push_back((float)j / 10.0);
			values.push_back(sp.Evaluate(vect));
		}
	int axeOfInsertion = 1;
	vector<vector<point>>& controlePoints = sp.tensor2;
	vector< vector<float>>& knots = sp.BS.knot;
	int degree = sp.BS.degree[axeOfInsertion];
	float knotToInsert = 0.5;
	
	knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
	for (int i = 0; i < 4;i++)
		ASSERT_EQ(controlePoints[i].size(), 5);

	// evaluation test
	int counter = 0;
	for (int i = 0;i < 11; i++)
		for (int j = 0;j < 11; j++)
		{
			vector<float> vect;
			vect.push_back((float)i / 10.0);
			vect.push_back((float)j / 10.0);
			point pt = sp.Evaluate(vect) - values[counter];
			EXPECT_NEAR(pt.getNorm(), 0, 0.01);
			counter++;
		}
}
