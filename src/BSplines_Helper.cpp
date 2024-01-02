#include "pch.h"
#include <iostream>
#include <vector>
#include"BSplines_Helper.h"
using namespace std;

#include <iostream>
#include <vector>
int ComputNumberOfBasisElts(int deg, vector<float>& knots)
{

    int sum = 0;
    set<float> knotsSet(knots.begin(), knots.end());
    for (float knot : knotsSet)
    {
        sum += countOccurrence(knots, knot);
    }
    return sum - 1 - deg;
}


int countOccurrence(const std::vector<float>& vec, float value) {
    int count = 0;

    // Iterate through the vector and count occurrences of the value
    for (const auto& element : vec) {
        if (element == value) {
            count++;
        }
    }

    return count;
}
int FindSpan(int NumberOfBasisElt, int deg, float u, vector <float >&knots)
{/* Determine the knot span index */
/* Input: n,p,u,U */
/* Return: the knot span index */
if (u == knots[NumberOfBasisElt + 1]) return(NumberOfBasisElt); /* Special case */
int low = deg;
int high = NumberOfBasisElt + 1; /* Do binary search */
float mid = (low + high) / 2;
while (u < knots[mid] || u >= knots[mid + 1])
{
	if (u < knots[mid]) high = mid;
	else low = mid;
	mid = (low + high) / 2;
}
return(mid);
}

int FindSpan( int deg, float u, vector <float >&knots)
{
    int NumberOfBasisElts=ComputNumberOfBasisElts(deg, knots);
    return FindSpan( NumberOfBasisElts, deg, u, knots);
}




// Cox-de Boor recursion formula for B-spline basis functions
double coxDeBoor(int Index, int deg, float u, const std::vector<float>& knots) {
    if (deg == 0) {
        if (knots[Index] <= u && u < knots[Index + 1]) {
            return 1.0;
        }
        else {
            return 0.0;
        }
    }
    else {
        double denom1 = knots[Index + deg ] - knots[Index];
        double denom2 = knots[Index + deg+1] - knots[Index + 1];

        double result = 0.0;

        if (denom1 != 0.0) {
            result += (u - knots[Index]) / denom1 * coxDeBoor(Index, deg - 1, u, knots);
        }

        if (denom2 != 0.0) {
            result += (knots[Index + deg+1] - u) / denom2 * coxDeBoor(Index + 1, deg - 1, u, knots);
        }

        return result;
    }
}

// Compute the derivative of a B-spline function
double bsplineDerivative(int Index, int deg, double u, const std::vector<float>& knots) {
    float result = 0;



    double denom1 = knots[Index + deg ] - knots[Index];
    double denom2 = knots[Index + deg+1] - knots[Index + 1];

 

    if (denom1 != 0.0) {
        float cox = coxDeBoor(Index, deg - 1, u, knots);
        result += cox*deg/ denom1  ;
    }

    if (denom2 != 0.0) {
        float cox= coxDeBoor(Index + 1, deg - 1, u, knots);
        result +=- deg/ denom2 * cox;
    }

    return result;
    
}
