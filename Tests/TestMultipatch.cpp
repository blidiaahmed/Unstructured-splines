#include "pch.h"
#include"ReadObj.h"
#include "WriteObj.h"
#include "splineFunctions.h"
#include"OBJMesh.h"
#include"MeshConvert.h"
#include"MultiPatch.h"
using namespace std;


TEST(Multipatch,SinglePatch)
{
	OBJMesh Om;
	Om.faces = { vector<int> {1,2,3,4 } };
	Om.points = { point({0,0,0}) ,point({1,0,0}) ,point({1,1,0}) ,point({0,1,0}) };
	
	multipatch mltp(ConvertObjToHEdge(Om));

	/*
	WriteOBJ("../models/test5.obj", mltp.Splines[0].ProduceOBJMesh());
	system("meshlab models/test5.obj");
	*/
}



TEST(Multipatch, Tube)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	/*
	WriteOBJ("../models/test0.obj", mltp.Splines[0].ProduceOBJMesh());
	WriteOBJ("../models/test1.obj", mltp.Splines[1].ProduceOBJMesh());
	WriteOBJ("../models/test2.obj", mltp.Splines[2].ProduceOBJMesh());
	WriteOBJ("../models/test3.obj", mltp.Splines[3].ProduceOBJMesh());
	WriteOBJ("../models/test4.obj", mltp.Splines[4].ProduceOBJMesh());
	system("meshlab models/test0.obj models/test1.obj models/test2.obj models/test3.obj models/test4.obj");
	*/
}

TEST(Multipatch, el3)
{
	OBJMesh Om = ReadObj("../models/el3.obj");
	multipatch mltp(ConvertObjToHEdge(Om));
	
	/*
	WriteOBJ("../models/test0.obj", mltp.Splines[0].ProduceOBJMesh());
	WriteOBJ("../models/test1.obj", mltp.Splines[1].ProduceOBJMesh());
	WriteOBJ("../models/test2.obj", mltp.Splines[2].ProduceOBJMesh());
	WriteOBJ("../models/test3.obj", mltp.Splines[3].ProduceOBJMesh());
	WriteOBJ("../models/test4.obj", mltp.Splines[4].ProduceOBJMesh());
	system("meshlab models/test0.obj models/test1.obj models/test2.obj models/test3.obj models/test4.obj");
	*/
}


TEST(TestMultipatch, RebuildSplinesFromControlVector)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	mltp.CreateControleVector();

	mltp.RebuildSplinesFromControlVector();
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
