#pragma once

class MatrixCoefficient {
public:
	int iIdx;
	int jIdx;
	float coef;
	//matrix index start from 0
	MatrixCoefficient(int i,int j,float cf):iIdx(i),jIdx(j),coef(cf){}
};
using namespace std;
class SparseMatrix {
public:
	
	int shape1 = 0;
	int shape2=0;
	vector<MatrixCoefficient> matrixCoefficients;
};
