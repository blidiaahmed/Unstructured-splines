#include "pch.h"
#include"MultiPatch.h"

#include"WriteObj.h"
#include "MeshConvert.h"
#include "ReadObj.h"


TEST(Multipatch_Evaluation, simple)
{
	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int face_Index = 1;
	
	vector <float> param = vector<float>{ 0.,0. };

	point pt=	mltp.EvaluateMultipatch_FaceBased(face_Index, param);
	
	EXPECT_EQ(point({ 0,0,0 }).getNorm(),pt.getNorm());
}

TEST(Multipatch_Evaluation, EdgeReferencedParameters)
{

	OBJMesh Om = ReadObj("../models/tube.obj");
	multipatch mltp(ConvertObjToHEdge(Om));

	int face_Index = 1;
	vector <float> param = vector<float>{ 0.,0. };

	vector <float> param_faceReference = vector<float>{ 1.,0. };

	point pt_faceReference = mltp.EvaluateMultipatch_FaceBased(face_Index, param_faceReference);

	int HalfEdgeIndex = mltp.HalfEdge_Mesh.faces[face_Index - 1].HEdge;

	int Next_HalfEdgeIndex = mltp.HalfEdge_Mesh.HalfeEdges[HalfEdgeIndex- 1].next;
	
	point pt = mltp.EvaluateMultipatch_EdgeBased(Next_HalfEdgeIndex, param);


	EXPECT_EQ(pt_faceReference.getNorm(), pt.getNorm());

}