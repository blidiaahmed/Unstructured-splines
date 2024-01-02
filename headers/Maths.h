#include <vector>
#pragma once
#include "point.h"
using namespace std;
int SelectIntervalIndex(float x, vector<float> t);
float evaluateSpline(float x, vector<float> t, int m // m is the number of knots
	, vector<float> c, int p // c are the controle points, d_i,0=c_i , p is the degree
	, int k // k is the knot interval index
);
point evaluateSpline(float x, vector<float> t, int m // m is the number of knots
	, vector<point> c, int p // c are the controle points, d_i,0=c_i , p is the degree
);
point evaluateSpline(float x, vector<float> t, int m // m is the number of knots
	, vector<point> c, int p // c are the controle points, d_i,0=c_i , p is the degree
	, int k // k is the knot interval index
);

point evaluateTensorSpline(vector<float> x, vector<vector<float>> t, vector<int> m // m is the number of knots
	, vector<vector<point>> c, vector<int> p // c are the controle points, d_i,0=c_i , p is the degree
	
);
float factorial(int n);

double binomial(int i, int n);