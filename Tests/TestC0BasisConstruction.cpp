#include "pch.h"
#include"MultiPatch.h"

#include"WriteObj.h"
#include "MeshConvert.h"
#include "ReadObj.h"


TEST(FunctionApproximation, ComputeHEdgesList_ArroundAVertex)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	int numberof3vertices = 0;
	int numberof1vertices = 0;
	int numberof2vertices=0;
	for (int i = 0; i < mltp.HalfEdge_Mesh.vertices.size(); i++)
	{

		Vertex vtx = mltp.HalfEdge_Mesh.vertices[i];

		int HE_Nb = mltp.ComputeHEdgesIndexesList_ArroundAVertex(vtx).size();
		if (HE_Nb == 3)numberof3vertices++;
		if (HE_Nb == 1)numberof1vertices++;
		if (HE_Nb == 2)numberof2vertices++;

	}

	EXPECT_EQ(numberof2vertices, 4);
	EXPECT_EQ(numberof3vertices, 4);
}


TEST(FunctionApproximation, BaseEvaluation_PartitionOfTheUnity)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	mltp.CreateControleVector();

	mltp.CreateG0Basis();

	//Number of basis elements
	EXPECT_EQ(mltp.G0Basis.shape1, 52);

	//Partition of the unity Test
	//take the sum of all basis elements and evaluate it at random parameters
	
	for (int i = 0;i < mltp.ControleVector[0].size();i++)
	{
		mltp.ControleVector[2][i] = 0;
	}
	for (int j = 0;j < mltp.G0Basis.matrixCoefficients.size();j++)
	{
		mltp.ControleVector
			[2]
			[mltp.G0Basis.matrixCoefficients[j].jIdx]
			+= 1;
	}
	
	mltp.RebuildSplinesFromControlVector();
	for (int faceIndex = 1;faceIndex <= mltp.Splines.size();faceIndex++)
	{
		vector <float> x = { 0.2,0.8 };

		EXPECT_EQ(mltp.EvaluateMultipatch_FaceBased(faceIndex, x).
			getCoordinate(2), 1);
	}


	/*
	int r = 10;

	WriteOBJ("../models/test0.obj", mltp.Splines[0].ProduceOBJMesh(r));
	WriteOBJ("../models/test1.obj", mltp.Splines[1].ProduceOBJMesh(r));
	WriteOBJ("../models/test2.obj", mltp.Splines[2].ProduceOBJMesh(r));
	WriteOBJ("../models/test3.obj", mltp.Splines[3].ProduceOBJMesh(r));
	WriteOBJ("../models/test4.obj", mltp.Splines[4].ProduceOBJMesh(r));
	system("meshlab ../models/test0.obj ../models/test1.obj ../models/test2.obj ../models/test3.obj ../models/test4.obj");
	*/

}
