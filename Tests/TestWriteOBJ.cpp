#include"pch.h"
#include <string>
#include"Example.h"
#include"WriteObj.h"
#include"OBJMesh.h"
#include"splineFunctions.h"
using namespace std;

TEST(WriteOBJ, OneTriangle)
{
	
	std::string str = "OBJfile.obj";
	OBJMesh Om;
	// 3 cordinates for position, then normals, then tesxture
	Om.points = { point({0,0,0,1,2,4,1,2,3}),point({0,0,1,1,2,3,1,2,3}),point({0,1,0,1,2,3,1,2,3}) };

	Om.faces = { {1,2,3}};
	WriteOBJ(str,Om);
	
	// debug
	// system("meshlab OBJfile.obj");

}

TEST(WriteOBJ, SplineSurface)
{
	
	OBJMesh Om;
	Example_SplineMesh( Om);
	string str = "objfile.obj";
	WriteOBJ(str, Om);

	//system("meshlab objfile.obj");
}

