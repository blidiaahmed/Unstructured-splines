#include "pch.h"
#include <cmath>
#include "Example.h"
#include "MultiPatch.h"
#include "HalfeEdge.h"
#include "Multipatch_Helper.h"

multipatch::multipatch(HalfEdgeMesh & hem)
{
	HalfEdge_Mesh = hem;
	for (int i = 0; i < hem.faces.size();i++)
	{
		Splines.push_back(spline(3));
		spline& sp = Splines[i];
		sp.BS = BSpline(2);
		tensor_example(sp.tensor2);

		Interpolation_QuadPatch(i+1, hem, sp);
	}	
}

point multipatch::EvaluateMultipatch_FaceBased(int face//face index
	, vector<float> FaceReferenced_Params)
{
	return Splines[face - 1].Evaluate(FaceReferenced_Params);
	
}

point multipatch::EvaluateMultipatch_EdgeBased(int HalfeEdgeNumber,
	vector<float> EdgeReferenced_Param)
{

	int faceIndex = HalfEdge_Mesh.HalfeEdges[HalfeEdgeNumber - 1].face;
	int HEdgeIndexInFace= HalfEdge_Mesh.HEdgeIndexInFace(HalfeEdgeNumber);
	vector <float> x = CoordinateChange_PatchParameter(EdgeReferenced_Param, HEdgeIndexInFace);
	return Splines[faceIndex - 1].Evaluate(x);
}

point multipatch::DeriveMultipatch_FaceBased(int face_Index, vector<float> FaceReferenced_Params, int Axe)
{
	return Splines[face_Index - 1].Derive(FaceReferenced_Params,Axe);
}

point multipatch::DeriveMultipatch_EdgeBased(int HalfeEdgeIndex, vector<float> FaceReferenced_Params,
	int Axe)
{
	int faceIndex = HalfEdge_Mesh.HalfeEdges[HalfeEdgeIndex - 1].face;
	int HEdgeIndexInFace = HalfEdge_Mesh.HEdgeIndexInFace(HalfeEdgeIndex);
	vector <float> x = CoordinateChange_PatchParameter(FaceReferenced_Params, 
		HEdgeIndexInFace);
	int signe = 1;
	point pt(3);
	if (HEdgeIndexInFace == 1)
	{
		 pt= Splines[faceIndex - 1].Derive(x, Axe);
	}
	else if (HEdgeIndexInFace == 2)
	{
		int Axe2 = (Axe + 1) % 2;
		if (Axe2==0)
			pt = -Splines[faceIndex - 1].Derive(x, Axe);
		else
			pt = Splines[faceIndex - 1].Derive(x, Axe);

	
	}
	else if (HEdgeIndexInFace == 3) 
	{
		pt = -Splines[faceIndex - 1].Derive(x, Axe);
	}
	else if (HEdgeIndexInFace == 4)
	{
		
		if (Axe == 0)
			pt = Splines[faceIndex - 1].Derive(x, Axe);
		else
			pt = -Splines[faceIndex - 1].Derive(x, Axe);
	}


	return pt;
}


int multipatch::previousFaces_CtrlPtsCounter(int face)
{
	int previousFaces_CtrlPtsCounter = 0;
	for (int faceIndex = 1;faceIndex < face;faceIndex++)
	{
		int CtrPtNb_PerOneFace = Splines[faceIndex - 1].BS.controlGridShape[0] *
			Splines[faceIndex - 1].BS.controlGridShape[1];
		previousFaces_CtrlPtsCounter += CtrPtNb_PerOneFace;
	}
	return previousFaces_CtrlPtsCounter;
}

void multipatch::CreatEdgeG1BasisElements() {}
void multipatch::CreatVertexG1BasisElements() {}

void multipatch::CreatInternalG1BasisElements()
{
	for (Face& f : HalfEdge_Mesh.faces)
	{
		HEdge& he = HalfEdge_Mesh.HalfeEdges[f.HEdge - 1];
		int EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];
		int OtherAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[0];

		for (int i = 1; i < EdgeAxeControlePointsNumber - 1;i++)
			for (int j = 1;j < OtherAxeControlePointsNumber - 1;j++)
			{
				int faceIndex = HalfEdge_Mesh.HalfeEdges[f.HEdge - 1].face;

				int CtrVectIdx = this->ControlVectorIndex(faceIndex, i, j);
				G1Basis.shape1++;
				MatrixCoefficient NewMatrixCoefficient(G1Basis.shape1 - 1, CtrVectIdx, 1.);
				G1Basis.shape2 = max(G1Basis.shape2, CtrVectIdx + 1);
				G1Basis.matrixCoefficients.push_back(NewMatrixCoefficient);
			}
	}
}

void multipatch::CreatInternalG0BasisElements()
{
	for (Face& f : HalfEdge_Mesh.faces)
	{
		HEdge& he = HalfEdge_Mesh.HalfeEdges[f.HEdge - 1];
		int EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];
		int OtherAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[0];

		for (int i = 1; i < EdgeAxeControlePointsNumber-1;i++)
			for (int j = 1;j < OtherAxeControlePointsNumber-1;j++)
			{
				int faceIndex=HalfEdge_Mesh.HalfeEdges[f.HEdge - 1].face;

				int CtrVectIdx=this->ControlVectorIndex(faceIndex,i, j );
				G0Basis.shape1++;
				MatrixCoefficient NewMatrixCoefficient(G0Basis.shape1-1, CtrVectIdx,1.);
				G0Basis.shape2 = max(G0Basis.shape2, CtrVectIdx + 1);
				G0Basis.matrixCoefficients.push_back(NewMatrixCoefficient);
			}
	}
}

void multipatch::CreatEdgeG0BasisElements()
{	
	int numberOfEdges = HalfEdge_Mesh.HalfeEdges.size();

	//flag edge that we passed through
	vector<bool> ifHedgeIsNotUsed(numberOfEdges,1);

	for (HEdge he : HalfEdge_Mesh.HalfeEdges )
	{
		int oppositEdgeIndex = he.twin-1;
		
		if (oppositEdgeIndex ==-2 || ifHedgeIsNotUsed[oppositEdgeIndex])
		{
			
			if (oppositEdgeIndex != -2)
			{
				// if not boundary: flag it
				int currentEdgeIndex = HalfEdge_Mesh.HalfeEdges[oppositEdgeIndex].twin - 1;
				ifHedgeIsNotUsed[oppositEdgeIndex] = 0;
				//need not to flag this hedge if it is a boundary edge, 
				ifHedgeIsNotUsed[currentEdgeIndex] = 0;
			}

			int EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];
			for (int i = 1;i < EdgeAxeControlePointsNumber - 1;i++)
			{
				int faceNumber = he.face;
				int iIndex_face = 0;
				int jIndex_face = 0;
				HalfEdgeBasedIndex_To_FaceBasedIndex(he, i, 0, faceNumber, iIndex_face, jIndex_face);
				int CtrVectIdx = this->ControlVectorIndex(faceNumber, iIndex_face, jIndex_face);
				int TwinEdge_CtrVectIdx = 0;
				if (oppositEdgeIndex != -2)
				{
					HEdge TwinHe = this->HalfEdge_Mesh.HalfeEdges[oppositEdgeIndex];
					int TwinfaceNumber = TwinHe.face;
					HalfEdgeBasedIndex_To_FaceBasedIndex(TwinHe, EdgeAxeControlePointsNumber-1-i, 0,
						TwinfaceNumber, iIndex_face, jIndex_face);
					 TwinEdge_CtrVectIdx = this->ControlVectorIndex(TwinfaceNumber,iIndex_face, jIndex_face);
				}

				G0Basis.shape1++;
				MatrixCoefficient NewMatrixCoefficient(G0Basis.shape1 - 1, CtrVectIdx, 1.);
				G0Basis.shape2 = max(G0Basis.shape2, CtrVectIdx + 1);
				G0Basis.matrixCoefficients.push_back(NewMatrixCoefficient);
				if (oppositEdgeIndex != -2)
				{
					NewMatrixCoefficient = MatrixCoefficient(G0Basis.shape1 - 1, TwinEdge_CtrVectIdx, 1.);
					G0Basis.matrixCoefficients.push_back(NewMatrixCoefficient);
				}
			}
		}
	}
}

vector<int> multipatch::ComputeHEdgesIndexesList_ArroundAVertex(Vertex vtx)
{
	vector<int> HEIndexVect(0);
	int InitialHEdgeNumber = vtx.HalfEdge;

	HEdge InitialHEdge = HalfEdge_Mesh.HalfeEdges[InitialHEdgeNumber - 1];
	HEIndexVect.push_back(InitialHEdgeNumber-1);
	
	Face fc = HalfEdge_Mesh.faces[InitialHEdge.face - 1];
	int nextEdgeIndex = HalfEdge_Mesh.
		Privious_Hedge_finder(&InitialHEdge, &fc)->twin - 1;
		
	HEdge CurrentHEdge;
	
	for (HEdge previousEdge = InitialHEdge;
		nextEdgeIndex >=0 &&
		nextEdgeIndex != InitialHEdgeNumber-1;
		)
	{
		HEIndexVect.push_back(nextEdgeIndex);
		CurrentHEdge = this->HalfEdge_Mesh.HalfeEdges[nextEdgeIndex];
		fc=HalfEdge_Mesh.faces[CurrentHEdge.face - 1];
		nextEdgeIndex = HalfEdge_Mesh.
		Privious_Hedge_finder(&CurrentHEdge, &fc)->twin - 1;
		previousEdge = CurrentHEdge;
	}
	// If the vertex is in the boundary, principle hedge may 
	// have HE on the right. We compute them next
	if (nextEdgeIndex < 0 && InitialHEdge.twin>0)
	{
		int nextEdgeIndex_FromRight = this->HalfEdge_Mesh.
			HalfeEdges[InitialHEdge.twin - 1].next - 1;
		CurrentHEdge = InitialHEdge;
		for (HEdge previousEdge = InitialHEdge;
			CurrentHEdge.twin >= 0;
			)
		{
		CurrentHEdge = this->
			HalfEdge_Mesh.HalfeEdges[nextEdgeIndex_FromRight];
		HEIndexVect.insert(HEIndexVect.cbegin(), nextEdgeIndex_FromRight);

		}
	}
		
	return HEIndexVect;
}

void multipatch::CreatVertexG0BasisElements()
{
	for (Vertex vtx : HalfEdge_Mesh.vertices)
	{
		vector<int> HEdgeIndexVect=ComputeHEdgesIndexesList_ArroundAVertex(vtx);
		G0Basis.shape1++;
		for (int HEdgeIndex : HEdgeIndexVect)
		{
			int iIndex_face;
			int jIndex_face;
			HEdge CurrentHEdge = HalfEdge_Mesh.HalfeEdges[HEdgeIndex];
			HalfEdgeBasedIndex_To_FaceBasedIndex(CurrentHEdge, 0,0,CurrentHEdge.face,
				iIndex_face, jIndex_face);
			int CtrVectIdx = this->ControlVectorIndex(CurrentHEdge.face,
				iIndex_face, jIndex_face);
			MatrixCoefficient NewMatrixCoefficient(G0Basis.shape1 - 1, CtrVectIdx, 1.);
			G0Basis.shape2 = max(G0Basis.shape2, CtrVectIdx + 1);
			G0Basis.matrixCoefficients.push_back(NewMatrixCoefficient);
		}

	}

}
void multipatch::CreateG0Basis()
{
	//Shape 1 will  be the number of basis elements
	//Shape 2 will be the same as the size of the contol vector
	G0Basis.shape2 = 0;
	G0Basis.shape1 = 0;
	CreatInternalG0BasisElements();

	CreatEdgeG0BasisElements();
	CreatVertexG0BasisElements();
}

void multipatch::CreateG1Basis()
{
	//Shape 1 will  be the number of basis elements
	//Shape 2 will be the same as the size of the contol vector
	G1Basis.shape2 = 0;
	G1Basis.shape1 = 0;
	CreatInternalG1BasisElements();

	CreatEdgeG1BasisElements();
	CreatVertexG1BasisElements();
}


void Interpolation_QuadPatch(int face, HalfEdgeMesh hem, spline& sp)

{
	Face* fc= &hem.faces[face - 1];
	HEdge he=hem.HalfeEdges[ fc->HEdge-1];
	vector<int> pointsIndeces;
	for (int i = 0; i < 4;i++)
	 {
		 pointsIndeces.push_back(he.vertex);
		 he = hem.HalfeEdges[he.next-1];

	 }
	Interpolation_QuadPatch(pointsIndeces, hem, sp);
}

void Interpolation_QuadPatch(vector<int> pointsIndeces, HalfEdgeMesh hem, spline& sp)
{
	vector <point> FacePoints;
	for (int i = 0;i < 4;i++)
		FacePoints.push_back(hem.vertices[pointsIndeces[i]-1].Point);
	interpolation_4points(FacePoints, sp);
	
}

void interpolation_4points(vector<point> FacePoints, spline& sp)
{
	point refPoint = FacePoints[0];
	point secondPoint = FacePoints[3];
	point Xaxis= FacePoints[1]-refPoint;
	point Xaxisp = FacePoints[2] -secondPoint;
	/*point Yaxis= FacePoints[3]-refPoint;
	point Yaxisp = FacePoints[2] - FacePoints[1];*/
	
	for (int i = 0; i < 4;i++) {
		point pt1 = refPoint + (i / 3.0) * Xaxis;
		point pt2 = secondPoint + (i / 3.0) * Xaxisp;
		point vect = pt2 - pt1;
		for (int j = 0;j < 4;j++)
		{
			point pt =pt1+(j / 3.0)* vect;
			//= refPoint + (i / 3.0) * Xaxis + (j / 3.0) * Yaxis;
			sp.tensor2[i][j] = pt;


		}
	}

}
