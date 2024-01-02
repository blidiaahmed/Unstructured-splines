#include "pch.h"
#include "SplinesDerivatives.h"
#include "knotInsertion_Splines.h"
#include "splineFunctions.h"
#include <iostream>


unsigned __int8 spline::getAmbiantDimension()
{
	return AmbiantDimension;
}

void spline::knotInsert(float knotToInsert, int axe)
{
	if (BS.ParametricDimension==1)
		knotInsertion::knotInsert(tensor1,BS.knot[0],  BS.degree[0],  knotToInsert);
	else if (BS.ParametricDimension == 2)
		knotInsertion::knotInsert(tensor2, BS.knot  , BS.degree[axe],knotToInsert, axe);
}

point spline::Evaluate(float x)
{


		vector<float> OutputCoordiantes;
		unsigned int controlPointsNumber = BS.getControlGridShape()[0];
		for (int i = 0;i < AmbiantDimension;i++)
		{
			vector<float > controlCoefficients;
			for (unsigned int j = 0;j < controlPointsNumber;j++)
			{
				controlCoefficients.push_back(tensor1[j].getCoordinate(i));
			}
			OutputCoordiantes.push_back(evaluateSpline(x, BS.knot[0], BS.knot[0].size(), controlCoefficients, BS.degree[0], BS.degree[0]));
		}
		point pt(OutputCoordiantes);
		return pt;
		
}
point spline::Evaluate(vector<float> x)
{
	vector<int > m;
	vector < int> p;
	for (int i = 0;i < BS.ParametricDimension;i++)
	{
		m.push_back(BS.knot[i].size());
		p.push_back((int) BS.degree[i]);

	}

	point pt (evaluateTensorSpline(x, BS.knot,m, tensor2,p ));
	return pt;

	
}

point spline::Derive(vector<float> x, int Axe)
{
	vector<int > m;
	vector < int> p;
	for (int i = 0;i < BS.ParametricDimension;i++)
	{
		m.push_back(BS.knot[i].size());
		p.push_back((int)BS.degree[i]);

	}
	if (Axe == 0)
	{
		point pt(evaluateTensorSplineDerivative_FirstAxe(x, BS.knot, m, tensor2, p));

		return pt;
	}
	else
	{
		point pt(evaluateTensorSplineDerivative_SecondAxe(x, BS.knot, m, tensor2, p));

		return pt;
	}

}
OBJMesh spline::ProduceOBJMesh()
{
	unsigned int precision = 5;
	return ProduceOBJMesh(precision);
}

OBJMesh spline::ProduceOBJMesh(int precision)
{
	OBJMesh Om;
	for (int i = 0; i <= precision;i++) {
		for (int j = 0; j<= precision;j++) {
			point pt = Evaluate({ (float)i / precision,(float)j / precision });
			Om.points.push_back(pt);
		}
	}

	for (int i = 0; i < precision
		;i++) {
		for (int j = 0; j < precision
			;j++) {
			vector<int> face{ (i )+1+ (j  )* (precision + 1),
				i+1+1  + (j ) * (precision + 1), 
				i+1  + (j+1 ) * (precision + 1) };
			
			Om.faces.push_back(face);
			face=vector<int>({ i + 1 + (j + 1) * (precision + 1) ,
				i + 1 + 1 + (j) * (precision + 1),i + 1 + 1 + (j+1) * (precision + 1) });
			Om.faces.push_back(face);

		}
	}
	return Om;
}