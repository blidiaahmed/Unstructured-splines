#include "pch.h"
#include"MultiPatch.h"
#include "MeshConvert.h"
#include "ReadObj.h"
#include "knotInsertion_Splines.h"
TEST(MultipatchControleVector,sizeTest)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	mltp.CreateControleVector();
	int VectorLength = 5 * mltp.Splines[0].BS.controlGridShape[0] * mltp.Splines[0].BS.controlGridShape[1];
	EXPECT_EQ(mltp.ControleVector[0].size(),VectorLength);
}


/*TEST(MultipatchControleVector, sizeTestOddGridShape)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	for (spline& sp : mltp.Splines)
	{
		int axeOfInsertion = 0;
		vector<vector<point>>& controlePoints = sp.tensor2;
		vector< vector<float>>& knots = sp.BS.knot;
		int degree = sp.BS.degree[axeOfInsertion];
		float knotToInsert = 0.5;

		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		axeOfInsertion = 1;
		
		 degree = sp.BS.degree[axeOfInsertion];

		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		sp.BS.computeControlGridShape(); 
	}
	mltp.CreateControleVector();
	
	int VectorLength = 5 * mltp.Splines[0].BS.controlGridShape[0] * mltp.Splines[0].BS.controlGridShape[1];
	EXPECT_EQ(mltp.ControleVector[0].size(), VectorLength);
}*/