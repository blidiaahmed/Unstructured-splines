#include "pch.h"

#include"MultiPatch.h"
#include"SplinesDerivatives.h"
#include"WriteObj.h"
#include"MeshConvert.h"
#include"ReadObj.h"



TEST(MultipatcheDerivation, FaceReferencedDerivationAxe1)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int face_Index = 1;
	float h = 0.0001;
	vector <float> param1 = vector<float>{ 0.58,0.33 };
	vector <float> param2 = vector<float>{ 0.58f+h,0.33 };
	int Axe = 0;
	point pt = mltp.DeriveMultipatch_FaceBased(face_Index, param1,Axe);
	point pt1 = mltp.EvaluateMultipatch_FaceBased(face_Index, param1);
	point pt2 = mltp.EvaluateMultipatch_FaceBased(face_Index, param2);
	pt2 = ((pt2 - pt1) * (1 / h));
	EXPECT_NEAR(pt2.getCoordinate(0), pt.getCoordinate(0),0.001);
	EXPECT_NEAR(pt2.getCoordinate(1), pt.getCoordinate(1),0.001);
}


TEST(MultipatcheDerivation, FaceReferencedDerivationAxe2)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int face_Index = 1;
	float h = 0.0001;
	vector <float> param1 = vector<float>{ 0.58,0.33 };
	vector <float> param2 = vector<float>{ 0.58f ,0.33f +h};
	int Axe = 1;
	point pt = mltp.DeriveMultipatch_FaceBased(face_Index, param1, Axe);
	point pt1 = mltp.EvaluateMultipatch_FaceBased(face_Index, param1);
	point pt2 = mltp.EvaluateMultipatch_FaceBased(face_Index, param2);
	pt2 = ((pt2 - pt1) * (1 / h));
	EXPECT_NEAR(pt2.getCoordinate(0), pt.getCoordinate(0), 0.001);
	EXPECT_NEAR(pt2.getCoordinate(1), pt.getCoordinate(1), 0.001);
}




TEST(MultipatcheDerivation, EdgeReferencedDerivationAxe2)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int EdgeNumber= 5;
	float h = 0.001;
	vector <float> param1 = vector<float>{ 0.68,0.33 };
	vector <float> param2 = vector<float>{ 0.68f ,0.33f + h };
	int Axe = 1;
	point pt = mltp.DeriveMultipatch_EdgeBased(EdgeNumber, param1, Axe);
	point pt1 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param1);
	point pt2 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param2);
	pt2 = ((pt2 - pt1) * (1 / h));
	EXPECT_NEAR(pt2.getCoordinate(0), pt.getCoordinate(0), 0.001);
	EXPECT_NEAR(pt2.getCoordinate(1), pt.getCoordinate(1), 0.001);

	EdgeNumber = mltp.HalfEdge_Mesh.HalfeEdges[EdgeNumber-1].next+1;
	pt = mltp.DeriveMultipatch_EdgeBased(EdgeNumber, param1, Axe);
	pt1 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param1);
	pt2 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param2);
	pt2 = ((pt2 - pt1) * (1 / h));
	EXPECT_NEAR(pt2.getCoordinate(0), pt.getCoordinate(0), 0.001);
	EXPECT_NEAR(pt2.getCoordinate(1), pt.getCoordinate(1), 0.001);

	EdgeNumber = mltp.HalfEdge_Mesh.HalfeEdges[EdgeNumber - 1].next+1;
	pt = mltp.DeriveMultipatch_EdgeBased(EdgeNumber, param1, Axe);
	pt1 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param1);
	pt2 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param2);
	pt2 = ((pt2 - pt1) * (1 / h));
	EXPECT_NEAR(pt2.getCoordinate(0), pt.getCoordinate(0), 0.001);
	EXPECT_NEAR(pt2.getCoordinate(1), pt.getCoordinate(1), 0.001);

	EdgeNumber = mltp.HalfEdge_Mesh.HalfeEdges[EdgeNumber - 1].next+1;
	pt = mltp.DeriveMultipatch_EdgeBased(EdgeNumber, param1, Axe);
	pt1 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param1);
	pt2 = mltp.EvaluateMultipatch_EdgeBased(EdgeNumber, param2);
	pt2 = ((pt2 - pt1) * (1 / h));
	EXPECT_NEAR(pt2.getCoordinate(0), pt.getCoordinate(0), 0.001);
	EXPECT_NEAR(pt2.getCoordinate(1), pt.getCoordinate(1), 0.001);
	
}