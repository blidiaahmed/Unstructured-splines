#pragma once
#include <vector>

using namespace std;

int FindSpan(int n, int p, float u, vector <float >&U);//inutile
int FindSpan( int p, float u, vector <float >&U);//inutile
int countOccurrence(const std::vector<float>& vec, float value);//inutile
int ComputNumberOfBasisElts(int deg, vector<float>& knots);//inutille


double bsplineDerivative(int i, int k, double t, const std::vector<float>& knots);
double coxDeBoor(int Index, int degP1, float u, const std::vector<float>& knots);
