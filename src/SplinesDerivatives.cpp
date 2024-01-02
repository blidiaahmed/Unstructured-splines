#include "pch.h"
#include"maths.h"
#include"BSplines_Helper.h"
#include"point.h"


point evaluateSplineDerivative(float u, vector<float> knots, vector<point> ControlPoints, int degree
)
{
	point pt(ControlPoints[0].getDimension());

	for (int k = 0;k < pt.getDimension();k++)
	{
		for (int i = 0;i < ControlPoints.size();i++)
		{
			pt.X[k] += bsplineDerivative(i, degree,u,knots)* ControlPoints[i].X[k];
		}
	}

	return pt;
}



point evaluateTensorSplineDerivative_FirstAxe(vector<float> u, vector<vector<float>> knots, vector<int> NbKnots // m is the number of knots
	, vector<vector<point>> ControlPoints, vector<int> degree
)
{
	vector<point> C;
	for (int i = 0; i < ControlPoints.size();i++)
	{
		C.push_back(evaluateSplineDerivative(u[0], knots[1], ControlPoints[i], degree[0]));
	}

	point pt(evaluateSpline(u[1], knots[0], NbKnots[1], C, degree[1]));
	return pt;
}

point evaluateTensorSplineDerivative_SecondAxe(vector<float> u, vector<vector<float>> knots, vector<int> NbKnots // m is the number of knots
	, vector<vector<point>> ControlPoints, vector<int> degree
)
{
	vector<point> C;
	for (int i = 0; i < ControlPoints.size();i++)
	{
		C.push_back(evaluateSpline(u[0], knots[1], NbKnots[0], ControlPoints[i], degree[0]));
	}

	point pt(evaluateSplineDerivative(u[1], knots[0], C, degree[1]));
	return pt;
}