#include"pch.h"
#include "MeshConvert.h"
#include"ReadObj.h"

TEST(MeshConvert, objToHEdgeMesh)
{
	HalfEdgeMesh hem;
	OBJMesh Om = ReadObj("../models/SimpleTest.obj");
	EXPECT_EQ(Om.faces.size(), 3);
	EXPECT_EQ(Om.points.size(), 4);
}	