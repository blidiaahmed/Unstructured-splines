#include "pch.h"
#include <vector>
#include "Maths.h"
//#include "point.h"
using namespace std;
float evaluateSpline(float x, vector<float> t, int m // m is the number of knots
	, vector<float> c, int p // c are the controle points, d_i,0=c_i , p is the degree
	, int k // k is the knot interval index
)
{
	float alpha = 0;
	vector< float> d(c);
	for (int r = 1; r <= p;r++)
	{
		vector<float> dd;
		for (int i = k - p + r;i <= k;i++)
		{
			alpha = (x - t[i]) / (t[i + 1 + p - r] - t[i]);
			 float val ((1 - alpha) * d[i - 1] + alpha * d[i]);
			dd.push_back(val);
		}
		for (int i = k - p + r;i <= k;i++)
		{

			d[i] = dd[i - k + p - r];
		}
	}
	return d[k];
}

int SelectIntervalIndex(float x,vector<float> t)
{
	int cmp = 0;
	for (int i = 0;i+1 < t.size();i++)
	{
		if (t[i] < t[i + 1]) 
		{ 
			cmp = i;
			if (t[i] <= x && x < t[i + 1])return i; 
		}
	}
	return cmp;
}

point evaluateSpline(float u, vector<float> knots, int NbKnots 
	, vector<point> ControlPoints, int degree 
)
{
	int k=SelectIntervalIndex( u,  knots);
	return evaluateSpline(u, knots, NbKnots, ControlPoints, degree, k);
}
point evaluateSpline(float u, vector<float> knots, int KnotsNumber 
	, vector<point> ControlPoints, int deg 
	, int SpanIndex 
)
{
	int n = KnotsNumber - SpanIndex - 1;
	float alpha = 0;
	vector< point> d(ControlPoints);
	for (int r = 1; r <= deg;r++)
	{
		vector<point> dd;
		for (int i = SpanIndex - deg + r;i <= SpanIndex;i++)
		{
			alpha = (u - knots[i]) / (knots[i + 1 + deg - r] - knots[i]);
			point val = (1 - alpha) * d[i - 1] + alpha * d[i];
			dd.push_back(val);
		}
		for (int i = SpanIndex - deg + r;i <= SpanIndex;i++)
		{

			d[i] = dd[i - SpanIndex + deg - r];
		}
	}
	return d[SpanIndex];
}

point evaluateTensorSpline(vector<float> x, vector<vector<float>> t, vector<int> m // m is the number of knots
	, vector<vector<point>> c, vector<int> p // c are the controle points, d_i,0=c_i , p is the degree
)
{
	vector<point> C; 
	for (int i = 0; i < c.size();i++)
	{		
		C.push_back(evaluateSpline(x[0], t[1], m[0], c[i], p[0]));
	}

	point pt(evaluateSpline(x[1], t[0], m[1], C, p[1]));
	return pt;
}
float factorial(int n)
{
	float f = 1;
	if (n == 0)
		return 1;
	for (int i = 1; i < n + 1;i++) 
	{
		f *= i;
	}
	return f;
}

double binomial(int i, int n)
{

	return factorial(n) / (factorial(i) * factorial(n - i));
}