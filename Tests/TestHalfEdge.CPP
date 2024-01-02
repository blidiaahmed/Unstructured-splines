#include "pch.h"
#include "png/CImg/CImg.h"

#include"splineFunctions.h"
#include"OBJMesh.h"
#include"WriteObj.h"
#include "HalfeEdge.h"
#include"MeshConvert.h"
#include"ReadObj.h"
#include"Example.h"
using namespace cimg_library;
using namespace std;
TEST(HalfeEdge, Constructors)
{
	OBJMesh Om = ReadObj("../models/SimpleTest.obj");
	HalfEdgeMesh hem(Om);

	EXPECT_EQ(hem.faces.size(), 3);
}


TEST(HalfEdge, SimpleHalfEdgeMesh_Evaluation)
{
	HalfEdgeMesh hem;
	OBJMesh Om;

	Om.points = vector<point >{ point({0,0,0}) ,point({1,0,0}),point({0,1,0}),point({-1,-1,0}) };
	Om.faces = vector<vector <int>>{ vector<int>{1,2,3} ,vector<int>{1,3,4} ,vector<int>{1,4,2} };

	hem = ConvertObjToHEdge(Om);

	EXPECT_EQ(hem.vertices.size(), Om.points.size());
	EXPECT_EQ(hem.faces.size(), Om.faces.size());

	vector<float> x1 = { 0,0 };
	point pt1 = hem.EvaluateHEMesh(x1, 1);
	EXPECT_EQ(pt1.getNorm(), 0);


	vector<float> x2 = { 0.25,0.25 };
	point pt2 = hem.EvaluateHEMesh(x2, 1);
	EXPECT_NEAR(pt2.getNorm(), 0.3535, 0.01);
}



TEST(HalfEdge, SplineSurfaceHalfeEdgeMesh_verticesOfOneFace)
{
	OBJMesh Om;
	Example_SplineMesh(Om);
	HalfEdgeMesh hem = ConvertObjToHEdge(Om);

	EXPECT_EQ(hem.vertices.size(), Om.points.size());
	EXPECT_EQ(hem.faces.size(), Om.faces.size());

	//debug
	//OBJMesh pointCloud;
	//vector<float> x1 = { 0.,0. };
	for (int j = 0; j < hem.faces.size(); j++)
	{
		int heElt = hem.faces[j].HEdge;
		int heElt_FirstElt = heElt;
		for (int i = 1;
			i <= 3
			;i++)
		{
			//debug
			//pointCloud.points.push_back(hem.EvaluateHEMesh(x1, heElt));
			heElt = hem.HalfeEdges[heElt - 1].next;
		}
		ASSERT_EQ(heElt, heElt_FirstElt);
	}
	/*
	WriteOBJ("../models/test3.obj", Om);
	WriteOBJ("../models/test2.obj", pointCloud);
	system("meshlab models/test2.obj models/test3.obj");
	*/
}

TEST(HalfEdge, SplineSurfaceHalfeEdgeMesh_Evaluation)
{
	OBJMesh Om;
	Example_SplineMesh(Om);
	HalfEdgeMesh hem = ConvertObjToHEdge(Om);

	EXPECT_EQ(hem.vertices.size(), Om.points.size());
	EXPECT_EQ(hem.faces.size(), Om.faces.size());

	OBJMesh pointCloud;
	vector<float> x1 = { 0.25,0.25 };
	for (int i = 1;
		i <= hem.faces.size()
		;i++)
	{
		pointCloud.points.push_back(hem.EvaluateHEMesh(x1, hem.faces[i-1].HEdge));
	}
	//debug
	/*
	WriteOBJ("../models/test3.obj", Om);
	WriteOBJ("../models/test2.obj", pointCloud);
	system("meshlab models/test2.obj models/test3.obj");
	*/
}

TEST(HalfEdge, FormingPointCloud)
{
	HalfEdgeMesh hem;
	OBJMesh Om;
	Om=ReadObj("../models/SimpleTest.obj");

	hem = ConvertObjToHEdge(Om);

	EXPECT_EQ(hem.vertices.size(), Om.points.size());
	EXPECT_EQ(hem.faces.size(), Om.faces.size());

	OBJMesh pointCloud;
	vector<float> x1 = { 0.1,0.1};
	for (int i=1;i<=hem.faces.size();i++)
	{
		pointCloud.points.push_back(hem.EvaluateHEMesh(x1, i));
	}

	//WriteOBJ("../models/test3.obj", Om);
	//WriteOBJ("../models/test2.obj", pointCloud);
	//system("meshlab models/test2.obj models/test3.obj");
}

TEST(HalfEdge, ReadPNG_PointCloud)
{

	OBJMesh Om;
	//prepare the image
	string str = "../models/CarteAltitude.bmp";
	
	// The Following is a time consuming part
	// You can execute it whene needed
	//PngToPointCloud(str, Om);
	//WriteOBJ("../models/test.obj", Om);
	//system("meshlab models/test.obj");
}



TEST(HalfEdge, FindHEdgeIndexInFace)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	HalfEdgeMesh hem(Om);
	for (int i = 0;i < hem.faces.size();i++)
	{
		int PrincipalEdge = hem.faces[i].HEdge;
		int NextHEdgeIndex = hem.HalfeEdges[PrincipalEdge - 1].next;
		int testedHEdge = hem.HEdgeIndexInFace(NextHEdgeIndex);
		EXPECT_EQ(testedHEdge, 2);

		NextHEdgeIndex = hem.HalfeEdges[testedHEdge - 1].next;
		testedHEdge = hem.HEdgeIndexInFace(NextHEdgeIndex);
		EXPECT_EQ(testedHEdge, 3);

		NextHEdgeIndex = hem.HalfeEdges[testedHEdge - 1].next;
		testedHEdge = hem.HEdgeIndexInFace(NextHEdgeIndex);
		EXPECT_EQ(testedHEdge, 4);

		NextHEdgeIndex = hem.HalfeEdges[testedHEdge - 1].next;
		testedHEdge = hem.HEdgeIndexInFace(NextHEdgeIndex);
		EXPECT_EQ(testedHEdge, 1);
	}

	

}