#pragma once

#include "HalfeEdge.h"
#include"splineFunctions.h"
#include"sparseMatrix.h"

class multipatch
{
public:
	HalfEdgeMesh HalfEdge_Mesh;
	vector<spline> Splines;
	//control vect 3 lines and each is coordinate
	vector<vector<float>> ControleVector;
	//Sparese matrix has, in each line, the control vector of a basis element 
	SparseMatrix G0Basis;
	SparseMatrix G1Basis;


	multipatch(HalfEdgeMesh &hem);

	void RebuildSplinesFromControlVector();
	void G0BasisToControlVector();
	void G1BasisToControlVector();
	void CreateControleVector();

	/**
	 * ControlVectorIndex
	 *
	 * return the index in the ControlVector corresponding to i,j and face.
	 *
	 * @param i,j,f indexes
	 * @return theindex of the function
	 */
	int ControlVectorIndex(int faceNumber, int iIndex, int jIndex);
	void  HalfEdgeBasedIndex_To_FaceBasedIndex(HEdge HEdg, int iIndex, int jIndex,
		int FaceNumber,int & iIndex_face, int & jIndex_face);
	int multipatch::ComputeNextTwinHEdgeIndex(HEdge he);

	void multipatch::CreatEdgeG1BasisElements();
	void multipatch::CreatVertexG1BasisElements();
	void multipatch::CreatInternalG1BasisElements();
	void CreatInternalG0BasisElements();
	void CreatEdgeG0BasisElements();

	vector<int> ComputeHEdgesIndexesList_ArroundAVertex(Vertex vtx);
	void CreatVertexG0BasisElements();
	void CreateG0Basis();
	void CreateG1Basis();
	
	point AccessControleVector(HEdge HEdg, int iIndex, int jIndex);
	point AccessControleVector(int faceNumber
		, int iIndex//start from zero
		, int jIndex//same
	);

	point EvaluateMultipatch_FaceBased(int face, vector <float> x);
	point EvaluateMultipatch_EdgeBased(int face_MainHEdge_Index, vector<float> param);

	point DeriveMultipatch_FaceBased(int face_Index, vector<float> param, int Axe);
	point DeriveMultipatch_EdgeBased(int face_Index,
		vector<float> EdgeReferenced_Params, int Axe);
	int previousFaces_CtrlPtsCounter(int face);
	void AddQuadFaceControlePoints(Face& f);
	void AddAQuarterFaceOfControlePoints(HEdge& he, int HalfEdgeIndexInFace);
	void ComputeQuarterLoopCounters(int& EdgeAxeLoopCounter,int& OtherAxeLoopCounter, 
		HEdge& he, int HalfEdgeIndexInFace);
	void AddCentralControlePoint(HEdge & he, int EdgeAxeControlePointsNumber, int OtherAxeControlePointsNumber);
};

void Interpolation_QuadPatch(int face, HalfEdgeMesh hem, spline& sp);
void Interpolation_QuadPatch(vector<int> pointsIndeces, HalfEdgeMesh hem, spline& sp);

void interpolation_4points(vector<point> FacePoints, spline & sp);