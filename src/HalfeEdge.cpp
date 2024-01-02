#include"pch.h"
#include"MeshConvert.h"
#include"HalfeEdge.h"




HalfEdgeMesh::HalfEdgeMesh(OBJMesh Om)
{
	*this= ConvertObjToHEdge(Om);
}

point HalfEdgeMesh::EvaluateHEMesh(vector<float> x, int hedgeIndex)
{

	HEdge* CurrentHalfeEdge = &HalfeEdges[hedgeIndex-1];
	Face* currentFace = &faces[CurrentHalfeEdge->face-1];


	point refPoint = vertices[CurrentHalfeEdge->vertex-1].Point;
	int NextHalfEdgeIndex = HalfeEdges[hedgeIndex - 1].next;
	int NextVertexIndex = HalfeEdges[NextHalfEdgeIndex - 1].vertex;
	point NextPoint = vertices[NextVertexIndex-1].Point;
	point XAxis = NextPoint - refPoint;
	HEdge* PreviousHalfeEdge = Privious_Hedge_finder(CurrentHalfeEdge, currentFace);
	point PreviousPoint = vertices[PreviousHalfeEdge->vertex-1].Point;
	point YAxis = PreviousPoint - refPoint;


	point pt = refPoint+x[0] * XAxis + x[1] * YAxis;;
	return pt;
}

HEdge* HalfEdgeMesh::Privious_Hedge_finder(HEdge* CurrentHalfEdge, Face* currentFace)
{
	int CurrentFaceEdgeNumber = currentFace->EdgesNumber;
	HEdge* Hedge_Cursor = CurrentHalfEdge;
	for (int counter = 1; counter < CurrentFaceEdgeNumber ;counter++)
	{

		Hedge_Cursor = &HalfeEdges[Hedge_Cursor->next-1];
	}
	
	return Hedge_Cursor;

}


//return 1 2 3 or 4
int HalfEdgeMesh::HEdgeIndexInFace(int  CurrentHalfEdgeIndex)
{
	HEdge CurrentHalfEdge = HalfeEdges[CurrentHalfEdgeIndex-1];
	
	
	int face=CurrentHalfEdge.face;
	int PrincipalHEdge = faces[face-1].HEdge;
	if (CurrentHalfEdgeIndex==PrincipalHEdge )return 1;
	int nextHEdge = CurrentHalfEdge.next;
	if (nextHEdge == PrincipalHEdge)return 4;

	CurrentHalfEdge = HalfeEdges[nextHEdge - 1];
	nextHEdge = CurrentHalfEdge.next;
	if (nextHEdge == PrincipalHEdge)return 3;

	CurrentHalfEdge = HalfeEdges[nextHEdge - 1];
	nextHEdge = CurrentHalfEdge.next;
	if (nextHEdge == PrincipalHEdge)return 2;

	return 0;
}
