#pragma once
#include"HalfeEdge.h"
#include "OBJMesh.h"
void Extract_HalfEdges_FromFaces(OBJMesh& Om, HalfEdgeMesh& HEM);
void CopyPoints(OBJMesh& Om, HalfEdgeMesh& HEM);
HalfEdgeMesh ConvertObjToHEdge(OBJMesh Om);
