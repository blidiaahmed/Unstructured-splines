#include "pch.h"
#include"MultiPatch.h"

#include"WriteObj.h"
#include "MeshConvert.h"
#include "ReadObj.h"
#include "knotInsertion_Splines.h"
TEST(MultipatchControleVector,sizeTestEvenGridShape)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	mltp.CreateControleVector();
	int VectorLength = 5 * mltp.Splines[0].BS.controlGridShape[0] * mltp.Splines[0].BS.controlGridShape[1];
	EXPECT_EQ(mltp.ControleVector[0].size(),VectorLength);
}


TEST(MultipatchControleVector, sizeTestOddGridShape)
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
}



TEST(Multipatch_AccessTheControleVector, EvenTimesEvenDimensionPatch)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	mltp.CreateControleVector();


	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2.size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				if(pt2.getNorm()!= pt.getNorm())
					cout<< faceIndex<< " "<< iIndex << " " << jIndex << endl;
				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}

}



TEST(Multipatch_AccessTheControleVector, EvenTimesEvenDimensionPatch2)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	float knotToInsert = 0.5;
	for (int patchIndex = 0;patchIndex < mltp.Splines.size();
		patchIndex++)
	{
		vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
		vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
		int axeOfInsertion = 0;
		int degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		axeOfInsertion = 1;
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}


	mltp.CreateControleVector();

	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2.size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];

				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}


TEST(Multipatch_AccessTheControleVector, OddTimesEvenDimension)
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
	
	mltp.CreateControleVector();
	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
			for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
			{
		for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
				{
					pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
					pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
					// debug
					if (pt2.getNorm() != pt.getNorm())
						cout << faceIndex << " " << iIndex << " " << jIndex << endl;

					EXPECT_EQ(pt2.getNorm(), pt.getNorm());
				}
			}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}



TEST(Multipatch_AccessTheControleVector, EvenTimesOddDimension)
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

	mltp.CreateControleVector();
	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				// debug
				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}



TEST(Multipatch_AccessTheControleVector, OddTimesOddDimension)
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

	mltp.CreateControleVector();
	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				// debug
				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}


TEST(Multipatch_AccessTheControleVector, Axe0TwoTimesLarger)
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

		controlePoints = mltp.Splines[patchIndex].tensor2;
		 knots = mltp.Splines[patchIndex].BS.knot;
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}

	mltp.CreateControleVector();
	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				// debug
				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}



TEST(Multipatch_AccessTheControleVector, Axe1TwoTimesLarger)
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

		controlePoints = mltp.Splines[patchIndex].tensor2;
		knots = mltp.Splines[patchIndex].BS.knot;
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}

	mltp.CreateControleVector();
	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				// debug
				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}



TEST(Multipatch_AccessTheControleVector, Shape5times7)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));



	for (int patchIndex = 0;patchIndex < mltp.Splines.size();
		patchIndex++)
	{
		int axeOfInsertion = 0;
		float knotToInsert = 0.5;
		vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
		vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
		int degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);

		axeOfInsertion = 1;
		controlePoints = mltp.Splines[patchIndex].tensor2;
		knots = mltp.Splines[patchIndex].BS.knot;
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);


		axeOfInsertion = 1;
		controlePoints = mltp.Splines[patchIndex].tensor2;
		knots = mltp.Splines[patchIndex].BS.knot;
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);

		axeOfInsertion = 1;
		controlePoints = mltp.Splines[patchIndex].tensor2;
		knots = mltp.Splines[patchIndex].BS.knot;
		degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
		knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);

		mltp.Splines[patchIndex].BS.computeControlGridShape();
	}

	mltp.CreateControleVector();
	int controleVectorSize = mltp.ControleVector[0].size();
	int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
	ASSERT_EQ(controlePointsNumber, controleVectorSize);

	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				// debug
				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}

	if (0)
	{
		// debug
		for (int i = 0; i < mltp.ControleVector[0].size();i++)
		{
			Om.points.push_back(point({ mltp.ControleVector[0][i],
				mltp.ControleVector[1][i], mltp.ControleVector[2][i] }));
		}
		WriteOBJ("test.obj", Om);
		system("meshlab test.obj");
	}
}

void AllKnotsInsertion(int NumberOfInsertedKnots_FirstAxe, int NumberOfInsertedKnots_SecondAxe, multipatch& mltp)
{
	int axeOfInsertion = 0;
	float knotToInsert = 0;
	for (int i = 1;i <= NumberOfInsertedKnots_FirstAxe;i++)
	{

		knotToInsert = i / (NumberOfInsertedKnots_FirstAxe + 1);
		for (int patchIndex = 0;patchIndex < mltp.Splines.size();
			patchIndex++)
		{
			vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
			vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
			int degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
			knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		}
	}
	axeOfInsertion = 1;
	for (int i = 1;i <= NumberOfInsertedKnots_SecondAxe;i++)
	{

		knotToInsert = i / (NumberOfInsertedKnots_SecondAxe + 1);
		for (int patchIndex = 0;patchIndex < mltp.Splines.size();
			patchIndex++)
		{
			vector<vector<point>>& controlePoints = mltp.Splines[patchIndex].tensor2;
			vector< vector<float>>& knots = mltp.Splines[patchIndex].BS.knot;
			int degree = mltp.Splines[patchIndex].BS.degree[axeOfInsertion];
			knotInsertion::knotInsert(controlePoints, knots, degree, knotToInsert, axeOfInsertion);
		}
	}
	for (int patchIndex = 0;patchIndex < mltp.Splines.size();
		patchIndex++)
	mltp.Splines[patchIndex].BS.computeControlGridShape();
}


void TestingMultipatchAccesControlVector(multipatch  &mltp)
{
	point pt;
	point pt2;
	for (int faceIndex = 1; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int jIndex = 0;jIndex < mltp.Splines[faceIndex - 1].tensor2[0].size();jIndex++)
		{
			for (int iIndex = 0;iIndex < mltp.Splines[faceIndex - 1].tensor2.size();iIndex++)
			{
				pt = mltp.AccessControleVector(faceIndex, iIndex, jIndex);
				pt2 = mltp.Splines[faceIndex - 1].tensor2[iIndex][jIndex];
				// debug
				if (pt2.getNorm() != pt.getNorm())
					cout << faceIndex << " " << iIndex << " " << jIndex << endl;

				EXPECT_EQ(pt2.getNorm(), pt.getNorm());
			}
		}

	}
}

TEST(Multipatch_AccessTheControleVector, BinarySearchForMistake_DegreeElevation)
{

	OBJMesh Om = ReadObj("../models/tube.obj");

	for (int NumberOfInsertedKnots_FirstAxe = 0;NumberOfInsertedKnots_FirstAxe < 5;NumberOfInsertedKnots_FirstAxe++)
	{
		for (int NumberOfInsertedKnotsSecondAxe = 0;NumberOfInsertedKnotsSecondAxe < 5;NumberOfInsertedKnotsSecondAxe++)
		{

			multipatch mltp(ConvertObjToHEdge(Om));
			AllKnotsInsertion(NumberOfInsertedKnots_FirstAxe, NumberOfInsertedKnotsSecondAxe, mltp);

			mltp.CreateControleVector();
			int controleVectorSize = mltp.ControleVector[0].size();
			int controlePointsNumber = mltp.Splines.size() * mltp.Splines[0].tensor2.size() * mltp.Splines[0].tensor2[0].size();
			ASSERT_EQ(controlePointsNumber, controleVectorSize);

			TestingMultipatchAccesControlVector(mltp);
		}
	}

	
}