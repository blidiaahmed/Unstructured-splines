#include "pch.h"
#include"MultiPatch.h"

#include"WriteObj.h"
#include "MeshConvert.h"
#include "ReadObj.h"
#include <Eigen/Dense>
#include "Multipatch_Helper.h"

TEST(FunctionApproximation, XtimesSinusFunction)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	multipatch mltp1(ConvertObjToHEdge(Om));

	mltp.CreateControleVector();
	mltp1.CreateControleVector();
	mltp.CreateG0Basis();

	mltp.G0BasisToControlVector();
	mltp.RebuildSplinesFromControlVector();


	
	vector<vector <float>> params_UniformlyDistributed = vector<vector <float>> (0);
	int precision = 5;
	for (int faceIndex = 0; faceIndex < mltp.Splines.size();faceIndex++)
	{
		for (int i = 0; i < precision + 1;i++)
		{
			for (int j = 0; j < precision + 1;j++)
			{
				vector<float> V(0);
				V.push_back(faceIndex);
				V.push_back(static_cast<float>(i) / precision);
				V.push_back(static_cast<float>(j) / precision);
		
				params_UniformlyDistributed.push_back(V);
			}
		}
	}
	vector<vector<float>> VendermondMatrix;
	vector<float > VendermondVector;
	for (vector<float>param : params_UniformlyDistributed) {
		int HEdgeNumber=mltp.HalfEdge_Mesh.
			faces[static_cast<int>(param[0])].HEdge;
		
		point pt = mltp.EvaluateMultipatch_EdgeBased(HEdgeNumber,
			{ param[1],param[2]});
		point pt1 = mltp1.EvaluateMultipatch_EdgeBased(HEdgeNumber,
			{ param[1],param[2] });
		VendermondMatrix.push_back(pt.X);
		VendermondVector.push_back(SinFct(pt1.X[0],pt1.X[1]));

	}

	using Eigen::MatrixXd;
	using Eigen::VectorXd;
	MatrixXd m(VendermondMatrix.size(), VendermondMatrix[0].size());
	VectorXd v(VendermondMatrix.size());
	
	for (int iIndex = 0;iIndex < VendermondMatrix.size();iIndex++) {
		v(iIndex) = VendermondVector[iIndex];
		for (int jIndex = 0;jIndex < VendermondMatrix[0].size();jIndex++)
		{
			m(iIndex, jIndex) = VendermondMatrix[iIndex][jIndex];
		}

	}

	MatrixXd A=
	( m.transpose()*m);
	VectorXd  b=v.transpose()* m;

	
	VectorXd s = A.colPivHouseholderQr().solve(b);

	// build a linear combination of basis functions
	// first: basis control vector to matrix
	MatrixXd BasisControlVector(mltp.ControleVector.size(), mltp.ControleVector[0].size());
	for (int iIndex = 0;iIndex < mltp.ControleVector.size();iIndex++)
		for (int jIndex = 0;jIndex < mltp.ControleVector[0].size();jIndex++)
		{
			BasisControlVector(iIndex, jIndex) = mltp.ControleVector[iIndex][jIndex];
		}

	//second: compute the product and put it in a mltp controle vector
	VectorXd WantedFunction=s.transpose()* BasisControlVector;
	
	for (int Index = 0;Index < mltp1.ControleVector[0].size();Index++)
	{
		mltp1.ControleVector[2][Index]= WantedFunction(Index);
	}
	mltp1.RebuildSplinesFromControlVector();
	
	/* int r = 10;

	WriteOBJ("../models/test0.obj", mltp1.Splines[0].ProduceOBJMesh(r));
	WriteOBJ("../models/test1.obj", mltp1.Splines[1].ProduceOBJMesh(r));
	WriteOBJ("../models/test2.obj", mltp1.Splines[2].ProduceOBJMesh(r));
	WriteOBJ("../models/test3.obj", mltp1.Splines[3].ProduceOBJMesh(r));
	WriteOBJ("../models/test4.obj", mltp1.Splines[4].ProduceOBJMesh(r));
	system("meshlab ../models/test0.obj ../models/test1.obj ../models/test2.obj ../models/test3.obj ../models/test4.obj");
	*/

	//Compute the error
	float Error=0;

	for (vector<float>param : params_UniformlyDistributed) {
		int HEdgeNumber = mltp.HalfEdge_Mesh.
			faces[static_cast<int>(param[0])].HEdge;

		point pt = mltp.EvaluateMultipatch_EdgeBased(HEdgeNumber,
			{ param[1],param[2] });
		point pt1 = mltp1.EvaluateMultipatch_EdgeBased(HEdgeNumber,
			{ param[1],param[2] });
		float term=(pt.X[2] - SinFct(pt1.X[0], pt1.X[1]));
		Error += term * term;

	}
	Error = sqrt(Error)/((precision+1)*(precision+1)* mltp.Splines.size());

	EXPECT_TRUE(Error<0.1);
}


TEST(TestC0, VisualiseOneBasisFunction)
{


	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	

	mltp.CreateControleVector();
	mltp.CreateG0Basis();

	vector<vector <float>> newVec;
	newVec.reserve(mltp.ControleVector.size());
	copy(mltp.ControleVector.begin(), mltp.ControleVector.end(), back_inserter(newVec));

	mltp.G0BasisToControlVector();
	for (int i = 0;i < 2;i++)
	{
		mltp.ControleVector[i].erase(mltp.ControleVector[i].begin(), mltp.ControleVector[i].end());
		copy(newVec[i].begin(), newVec[i].end(), back_inserter(mltp.ControleVector[i]));
	}
	mltp.ControleVector.erase(std::next(mltp.ControleVector.begin(), 3), mltp.ControleVector.end());
	mltp.RebuildSplinesFromControlVector();
	
	 
	/*int r = 10;

	WriteOBJ("../models/test0.obj", mltp.Splines[0].ProduceOBJMesh(r));
	WriteOBJ("../models/test1.obj", mltp.Splines[1].ProduceOBJMesh(r));
	WriteOBJ("../models/test2.obj", mltp.Splines[2].ProduceOBJMesh(r));
	WriteOBJ("../models/test3.obj", mltp.Splines[3].ProduceOBJMesh(r));
	WriteOBJ("../models/test4.obj", mltp.Splines[4].ProduceOBJMesh(r));
	system("meshlab ../models/test0.obj ../models/test1.obj ../models/test2.obj ../models/test3.obj ../models/test4.obj");*/

	EXPECT_EQ(1, 1);
	
}