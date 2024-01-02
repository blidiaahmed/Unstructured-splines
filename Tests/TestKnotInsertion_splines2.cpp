#include"pch.h"
#include"Example.h"
#include"knotInsertion_Splines.h"
#include"splineFunctions.h"


TEST(TestkontInsertion_spline, UnchangebilityOfTheFunction1)
{

	spline sp(1);
	sp.tensor1 = vector<point>({ point({0,0}),point({1,0}),point({0,0}),point({1,0}) });
	vector<point> values;
	for (int i = 0;i < 11; i++)
	{
		values.push_back(sp.Evaluate(i / 10.0));
	}
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.5);
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.5);
	ASSERT_EQ(sp.tensor1.size(), 6);
	float error = 0;

	for (int i = 0;i < 11; i++)
	{
		point ptt = values[i];
		point pt = values[i] - sp.Evaluate(i / 10.0);
		error += pt.getNorm();
	}
	ASSERT_NEAR(error, 0, 0.001);
}

TEST(TestkontInsertion_spline, UnchangebilityOfTheFunction2)
{

	spline sp(1);
	sp.tensor1 = vector<point>({ point({0,0}),point({1,0}),point({0,0}),point({1,0}) });
	vector<point> values;
	for (int i = 0;i < 11; i++)
	{
		values.push_back(sp.Evaluate(i / 10.0));
	}
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.25);
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.75);
	ASSERT_EQ(sp.tensor1.size(), 6);
	float error = 0;

	for (int i = 0;i < 11; i++)
	{
		point ptt = values[i];
		point pt = values[i] - sp.Evaluate(i / 10.0);
		error += pt.getNorm();
	}
	ASSERT_NEAR(error, 0, 0.001);
}


TEST(TestkontInsertion_spline, UnchangebilityOfTheFunction3)
{

	spline sp(1);
	sp.tensor1 = vector<point>({ point({0,0}),point({1,0}),point({0,0}),point({1,0}) });
	vector<point> values;
	for (int i = 0;i < 11; i++)
	{
		values.push_back(sp.Evaluate(i / 10.0));
	}
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.25);
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.5);
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.75);
	ASSERT_EQ(sp.tensor1.size(), 7);
	float error = 0;

	for (int i = 0;i < 11; i++)
	{
		point ptt = values[i];
		point pt = values[i] - sp.Evaluate(i / 10.0);
		error += pt.getNorm();
	}
	ASSERT_NEAR(error, 0, 0.001);
}

TEST(TestkontInsertion_spline, UnchangebilityOfTheFunction4)
{

	spline sp(1);
	int parametricDimension = 1;

	vector<unsigned int> degree = vector<unsigned int>({ 2u });
	vector<vector<float>> knotsDistribution = vector<vector<float>>({ vector<float>({0,0,0,1,1,1}) });
	sp.BS = BSpline(parametricDimension, degree, knotsDistribution);
	sp.tensor1 = vector<point>({ point({0,0}),point({1,0}),point({0,0}) });
	vector<point> values;
	for (int i = 0;i < 11; i++)
	{
		values.push_back(sp.Evaluate(i / 10.0));
	}
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.25);
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.5);
	knotInsertion::knotInsert(sp.tensor1, sp.BS.knot[0], sp.BS.degree[0], 0.75);
	ASSERT_EQ(sp.tensor1.size(), 6);
	float error = 0;

	for (int i = 0;i < 11; i++)
	{
		point ptt = values[i];
		point pt = values[i] - sp.Evaluate(i / 10.0);
		error += pt.getNorm();
	}
	ASSERT_NEAR(error, 0, 0.001);
}

