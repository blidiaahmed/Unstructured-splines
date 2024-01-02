#include <vector>
#pragma once 
#include "pch.h"
#include"OBJMesh.h"
#include "point.h"
#include "BSpline.h"
#include"Maths.h"
using namespace std;
class spline
{
public:
	BSpline BS;


	vector<point> tensor1;
	vector<vector<point>> tensor2;

	unsigned __int8 AmbiantDimension = 1;

	unsigned __int8 getAmbiantDimension();
	// Constructors
	spline():BS(), tensor1() {};
	spline(unsigned __int8 dim) :AmbiantDimension(dim), BS() 
	{
		 tensor1= vector<point>();
	};
	spline(unsigned int dim,
		vector<unsigned int> degreeVector,
		vector< vector<float>> knotVector) :AmbiantDimension(dim), 
		BS( dim,
			 degreeVector,
			 knotVector

			)
	{
		tensor1 = vector<point>();
	};
	//knot insertion
	void knotInsert(float knotToInsert, int axe);

	//evaluation function
	point Evaluate(float x);
	point Evaluate(vector<float> x);
	point Derive(vector<float> x,int Axe);

	//produce mesh
	OBJMesh ProduceOBJMesh();
	OBJMesh ProduceOBJMesh(int precision);
};



