#include "pch.h"
#include "MeshConvert.h"
#include"HalfeEdge.h"



HalfEdgeMesh ConvertObjToHEdge(OBJMesh Om)
{
	HalfEdgeMesh HEM;

	// copy points
	CopyPoints(Om, HEM);

	Extract_HalfEdges_FromFaces(Om, HEM);

	return HEM;
}

void Extract_HalfEdges_FromFaces(OBJMesh& Om, HalfEdgeMesh& HEM)
{

	for (vector<int>& fc : Om.faces)
	{
		HEM.faces.push_back(Face());
		Face& CurrentFace = HEM.faces[HEM.faces.size() - 1];
		CurrentFace.EdgesNumber = fc.size();
		for (int index = 0;index < CurrentFace.EdgesNumber;index++)
		{
			HEM.HalfeEdges.push_back(HEdge());
			HEdge& CurrentHalfEdge = HEM.HalfeEdges.back();
			CurrentHalfEdge.vertex = fc[index];

			//compute the edge corresponding to he
			int  nextIndex = (index < fc.size() - 1) ? index + 1 : 0;
			set<int> CurrentEdge_VerticesSet = { fc[index],fc[nextIndex] };

			//specify the edge in he
			CurrentHalfEdge.Edge = CurrentEdge_VerticesSet;

			//find the edge
			set<set<int>>::iterator it = HEM.SetEdges.find(CurrentEdge_VerticesSet);

			if (it == HEM.SetEdges.end())
			{
				HEM.SetEdges.insert(CurrentEdge_VerticesSet);
				HEM.edges[CurrentEdge_VerticesSet] = edge();
				HEM.edges[CurrentEdge_VerticesSet].HEdge = HEM.HalfeEdges.size();
				//in this case the twin is not known yet (and may not exist if boundary edge)
			}
			else
			{
				// in this case the twin is known and need to be linked to the current hedge
				CurrentHalfEdge.twin = HEM.edges[CurrentEdge_VerticesSet].HEdge;
				HEM.HalfeEdges[HEM.edges[CurrentEdge_VerticesSet].HEdge - 1].twin = HEM.HalfeEdges.size();
			}

			//next half edge
			if (index < CurrentFace.EdgesNumber - 1)
			{
				CurrentHalfEdge.next = HEM.HalfeEdges.size() + 1;
			}
			else
			{
				CurrentHalfEdge.next = HEM.HalfeEdges.size() - CurrentFace.EdgesNumber + 1;
			}

			// specify the face
			CurrentHalfEdge.face = HEM.faces.size();

			// associate to the current vertex  the current halfe edge
			HEM.vertices[fc[index] - 1].HalfEdge = HEM.HalfeEdges.size();

			if (index == 0)
			{
				CurrentFace.HEdge = HEM.HalfeEdges.size();
			}
		}
	}
}

void CopyPoints(OBJMesh& Om, HalfEdgeMesh& HEM)
{
	for (point pt : Om.points)
	{
		Vertex vrt;

		vrt.Point = pt;
		vrt.HalfEdge = -1;
		HEM.vertices.push_back(vrt);

	}
}
