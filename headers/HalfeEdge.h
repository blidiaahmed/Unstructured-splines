#include <iostream>

#pragma once

#include"point.h"
#include "OBJMesh.h"
using namespace std;

// Important remark
// all integers start from one HalfEdge, face... but when replace in vector put integer-1
// example: in face the principal halfelge is an integer "int HEdge=-1;" larger than 1, 
// but when replaced in the vector we put HEdge-1;


class Vertex
{
public:
	int HalfEdge = -1;
	//additional
	
	point Point;

};
class HEdge
{
public:
	int twin = -1;// stay -1 if boundary edge
	int next = -1;
	int vertex = -1;
	int face = -1;
	set<int> Edge; 
	HEdge() {
		Edge = {};
	}

};

class edge
{
public:
	int HEdge;
	//additional
	/*set<int> vertices;
	int index;*/

};
class Face
{
public:
	int HEdge=-1;
	int EdgesNumber = -1;
};

class HalfEdgeMesh
{
public:
	vector<Vertex> vertices;
	vector<HEdge> HalfeEdges;
	vector<Face> faces;
	//vector<edge> edges;
	map<set<int>,edge> edges;
	set<set<int>> SetEdges;//two coordinates for vertex index, and the last gives the edge index
	//constructor
	HalfEdgeMesh() = default;
	HalfEdgeMesh(OBJMesh Om);
	
	point EvaluateHEMesh(vector<float> x, int hedgeIndex);
	HEdge* HalfEdgeMesh::Privious_Hedge_finder(HEdge* CurrentHalfeEdge, Face* currentFace);
	int HEdgeIndexInFace(int  CurrentHalfeEdgeIndex);
};

