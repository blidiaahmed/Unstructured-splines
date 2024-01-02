#include "pch.h"
#include"sparseMatrix.h"
using namespace std;
TEST(SparseMatrix, Simple)
{
	SparseMatrix spM;
	
	spM.matrixCoefficients = vector<MatrixCoefficient>{ MatrixCoefficient{0,0,1.}};
	spM.matrixCoefficients.push_back(MatrixCoefficient{ 0,0,1. });

}