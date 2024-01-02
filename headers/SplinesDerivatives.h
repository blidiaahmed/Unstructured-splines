#pragma once
#include"BSplines_Helper.h"
#include "point.h"


point evaluateSplineDerivative(float u, vector<float> knots, vector<point> ControlPoints, int degree
);
point evaluateTensorSplineDerivative_SecondAxe(vector<float> u, vector<vector<float>> knots, vector<int> NbKnots // m is the number of knots
	, vector<vector<point>> ControlPoints, vector<int> degree
);

point evaluateTensorSplineDerivative_FirstAxe(vector<float> u, vector<vector<float>> knots, vector<int> NbKnots // m is the number of knots
	, vector<vector<point>> ControlPoints, vector<int> degree
);