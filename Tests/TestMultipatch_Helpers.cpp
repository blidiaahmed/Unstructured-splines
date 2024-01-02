#include "pch.h"
#include"MultiPatch.h"

#include"WriteObj.h"
#include "MeshConvert.h"
#include "ReadObj.h"
#include "knotInsertion_Splines.h"
#include "Multipatch_Helper.h"

TEST(Multipatch_Helpers, whichQuarter_WhichIndexInCtrVector_QuarterDimension_EvenEven)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	mltp.CreateControleVector();
	int face = 1;
	vector<vector<unsigned>> QuartersDimensions;
	int EdgeAxeControlePointsNumber = 4;
	int OtherAxeControlePointsNumber = 4;
	ComputeQuartersDimensions(QuartersDimensions, face, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(QuartersDimensions[0][0], 2);
	ASSERT_EQ(QuartersDimensions[0][1], 2);

	int iIndex=0;
	int jIndex=0;
	ASSERT_EQ(whichQuarter(QuartersDimensions, iIndex, jIndex, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);


	int WchQuarter = 1;
	iIndex = 0;
	jIndex = 0;
	int wchIdx = WhichIndexInCtrVector(WchQuarter, iIndex, jIndex, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 0);
	 wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 1);
	 wchIdx = WhichIndexInCtrVector(WchQuarter, 0,1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 2);
	 wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 3);
	
	WchQuarter = 2;
	wchIdx = WhichIndexInCtrVector(WchQuarter ,3, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 4);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 5);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 6);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 7);

	WchQuarter = 3;
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 8);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 9);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 10);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 11);

	WchQuarter = 4;
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 12);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 13);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 14);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 15);

}

TEST(Multipatch_Helpers, whichQuarter_WhichIndexInCtrVector_QuarterDimension_OddEven)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int axeOfInsertion = 0;
	float knotToInsert = 0.5;
	for (int patchIndex = 0;patchIndex < mltp.Splines.size();
		patchIndex++)
	{
		vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
		vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
		int degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}

	int face = 1;
	vector<vector<unsigned>> QuartersDimensions;
	int EdgeAxeControlePointsNumber = mltp.Splines[0].tensor2.size();
	int OtherAxeControlePointsNumber = mltp.Splines[0].tensor2[0].size();
	ComputeQuartersDimensions(QuartersDimensions, face, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(QuartersDimensions[0][0], 3);
	ASSERT_EQ(QuartersDimensions[0][1], 2);
	ASSERT_EQ(QuartersDimensions[1][0], 2);
	ASSERT_EQ(QuartersDimensions[1][1], 2);
	ASSERT_EQ(QuartersDimensions[2][0], 3);
	ASSERT_EQ(QuartersDimensions[2][1], 2);
	ASSERT_EQ(QuartersDimensions[3][0], 2);
	ASSERT_EQ(QuartersDimensions[3][1], 2);


	int iIndex = 0;
	int jIndex = 0;
	ASSERT_EQ(whichQuarter(QuartersDimensions, iIndex, jIndex, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);


	int WchQuarter = 1;
	iIndex = 0;
	jIndex = 0;
	int wchIdx = WhichIndexInCtrVector(WchQuarter, iIndex, jIndex, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 0);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 1);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 2);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 3);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 4);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 5);

	WchQuarter = 2;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 6);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 7);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 8);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 9);

	WchQuarter = 3;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 10);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 11);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 12);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 13);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 14);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 15);

	WchQuarter = 4;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 16);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 17);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 18);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	EXPECT_EQ(wchIdx, 19);

}

TEST(Multipatch_Helpers, whichQuarter_WhichIndexInCtrVector_QuarterDimension_EvenOdd)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int axeOfInsertion = 1;
	float knotToInsert = 0.5;
	for (int patchIndex = 0;patchIndex < mltp.Splines.size();
		patchIndex++)
	{
		vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
		vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
		int degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}

	int face = 1;
	vector<vector<unsigned>> QuartersDimensions;
	int EdgeAxeControlePointsNumber = mltp.Splines[0].tensor2.size();
	int OtherAxeControlePointsNumber = mltp.Splines[0].tensor2[0].size();
	ComputeQuartersDimensions(QuartersDimensions, face, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(QuartersDimensions[0][0], 2);
	ASSERT_EQ(QuartersDimensions[0][1], 2);
	ASSERT_EQ(QuartersDimensions[1][0], 3);
	ASSERT_EQ(QuartersDimensions[1][1], 2);
	ASSERT_EQ(QuartersDimensions[2][0], 2);
	ASSERT_EQ(QuartersDimensions[2][1], 2);
	ASSERT_EQ(QuartersDimensions[3][0], 3);
	ASSERT_EQ(QuartersDimensions[3][1], 2);


	int iIndex = 0;
	int jIndex = 0;
	ASSERT_EQ(whichQuarter(QuartersDimensions, iIndex, jIndex, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	

	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);


	int WchQuarter = 1;
	iIndex = 0;
	jIndex = 0;
	int wchIdx = WhichIndexInCtrVector(WchQuarter, iIndex, jIndex, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 0);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 1);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 2);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 3);

	WchQuarter = 2;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 4);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 5);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 6);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 7);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 8);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 9);

	WchQuarter = 3;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 10);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 11);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 12);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 13);

	WchQuarter = 4;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 14);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 15);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 16);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 17);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 18);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 19);

	

}

TEST(Multipatch_Helpers, whichQuarter_WhichIndexInCtrVector_QuarterDimension_OddOdd)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int FirstaxeOfInsertion = 0;
	int SecondaxeOfInsertion = 1;
	float knotToInsert = 0.5;
	for (int patchIndex = 0;patchIndex < mltp.Splines.size();
		patchIndex++)
	{
		vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
		vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
		int degree = mltp.Splines[patchIndex].BS.degree[FirstaxeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, FirstaxeOfInsertion);
		degree = mltp.Splines[patchIndex].BS.degree[SecondaxeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, SecondaxeOfInsertion);
		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}

	int face = 1;
	vector<vector<unsigned>> QuartersDimensions;
	int EdgeAxeControlePointsNumber = mltp.Splines[0].tensor2.size();
	int OtherAxeControlePointsNumber = mltp.Splines[0].tensor2[0].size();
	ComputeQuartersDimensions(QuartersDimensions, face, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(QuartersDimensions[0][0], 3);
	ASSERT_EQ(QuartersDimensions[0][1], 2);
	ASSERT_EQ(QuartersDimensions[1][0], 3);
	ASSERT_EQ(QuartersDimensions[1][1], 2);
	ASSERT_EQ(QuartersDimensions[2][0], 3);
	ASSERT_EQ(QuartersDimensions[2][1], 2);
	ASSERT_EQ(QuartersDimensions[3][0], 3);
	ASSERT_EQ(QuartersDimensions[3][1], 2);



	int iIndex = 0;
	int jIndex = 0;
	ASSERT_EQ(whichQuarter(QuartersDimensions, iIndex, jIndex, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2,0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1,0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 1);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 0, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 1, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 2);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 4, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 3, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 3);


	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 3, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 0, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);
	ASSERT_EQ(whichQuarter(QuartersDimensions, 1, 4, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 4);

	ASSERT_EQ(whichQuarter(QuartersDimensions, 2, 2, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber), 5);


	int WchQuarter = 1;
	iIndex = 0;
	jIndex = 0;
	int wchIdx = WhichIndexInCtrVector(WchQuarter, iIndex, jIndex, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 0);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 1);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 2);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 3);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 4);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 5);

	WchQuarter = 2;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 6);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 7);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 8);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 0, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 9);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 1, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 10);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 11);

	WchQuarter = 3;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 12);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3,4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 13);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 14);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 4, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 15);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 3, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 16);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 2, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 17);

	WchQuarter = 4;

	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 18);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 19);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 0, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 20);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 4, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 21);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 3, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 22);
	wchIdx = WhichIndexInCtrVector(WchQuarter, 1, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 23);

	wchIdx = WhichIndexInCtrVector(5, 2, 2, QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	ASSERT_EQ(wchIdx, 24);
}
TEST(Multipatch_Helpers, CoordinateChange_PatchParameter)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	int face_Index = 1;

	vector <float> Param_EdgeReferenced = vector<float>{ 0.2,0.3 };

	int HEdgeIndex = mltp.HalfEdge_Mesh.faces[face_Index - 1].HEdge;
	int Next_HEdgeIndex = mltp.HalfEdge_Mesh.HalfeEdges[HEdgeIndex - 1].next;
	int HEdgeIndexInFace = mltp.HalfEdge_Mesh.HEdgeIndexInFace(Next_HEdgeIndex);
	vector <float> param_faceReference = CoordinateChange_PatchParameter(Param_EdgeReferenced, HEdgeIndexInFace);
	EXPECT_NEAR(param_faceReference[0], 0.7,0.1);
	EXPECT_NEAR(param_faceReference[1], 0.2,0.1);

	Next_HEdgeIndex = mltp.HalfEdge_Mesh.HalfeEdges[Next_HEdgeIndex - 1].next;
	HEdgeIndexInFace = mltp.HalfEdge_Mesh.HEdgeIndexInFace(Next_HEdgeIndex);
	param_faceReference = CoordinateChange_PatchParameter(Param_EdgeReferenced, HEdgeIndexInFace);
	EXPECT_NEAR(param_faceReference[0], 0.8,0.01);
	EXPECT_NEAR(param_faceReference[1], 0.7,0.01);

	Next_HEdgeIndex = mltp.HalfEdge_Mesh.HalfeEdges[Next_HEdgeIndex - 1].next;
	HEdgeIndexInFace = mltp.HalfEdge_Mesh.HEdgeIndexInFace(Next_HEdgeIndex);
	param_faceReference = CoordinateChange_PatchParameter(Param_EdgeReferenced, HEdgeIndexInFace);
	EXPECT_NEAR(param_faceReference[0], 0.3,0.1);
	EXPECT_NEAR(param_faceReference[1], 0.8,0.1);
}