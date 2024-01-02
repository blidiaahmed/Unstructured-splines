#include "pch.h"
#include "MultiPatch.h"
#include "Multipatch_Helper.h"

void multipatch::CreateControleVector()
{
	ControleVector.clear();
	int ambiantDimension = Splines[0].AmbiantDimension;
	for (unsigned __int8 i = 0;i < ambiantDimension;i++)
		ControleVector.push_back(vector<float>());
	for (Face& f : HalfEdge_Mesh.faces)
		AddQuadFaceControlePoints(f);
}



int multipatch::ControlVectorIndex(int faceNumber, int iIndex, int jIndex)
{
	int previousFaces_CtrlPtsNb = this->previousFaces_CtrlPtsCounter(faceNumber);
	Face fc = HalfEdge_Mesh.faces[faceNumber - 1];
	HEdge he = HalfEdge_Mesh.HalfeEdges[fc.HEdge - 1];
	int EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[0];
	int OtherAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];
	vector<vector<unsigned>> QuartersDimensions;

	ComputeQuartersDimensions(QuartersDimensions, faceNumber, 
		EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	int WchQuarter = whichQuarter(QuartersDimensions, iIndex, jIndex,
		EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	int indexInCtrVector = WhichIndexInCtrVector(WchQuarter, iIndex, jIndex,
		QuartersDimensions, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	int returnIndex = previousFaces_CtrlPtsNb + indexInCtrVector;
	return returnIndex;
}
point multipatch::AccessControleVector(int faceNumber, int iIndex, int jIndex)
{
	
	int ControlVectorIndex= this->ControlVectorIndex(faceNumber, iIndex, jIndex);
	

	point pt = point({ ControleVector[0][ControlVectorIndex],ControleVector[1][ControlVectorIndex] });
	for (int Index = 2;Index < ControleVector.size();Index++)
	{
		pt.X.push_back(ControleVector[Index][ControlVectorIndex]);
	}
	pt.dimension = ControleVector.size();
	return pt;

}


void  multipatch::HalfEdgeBasedIndex_To_FaceBasedIndex(HEdge HEdg,  int iIndex, int jIndex,
	int FaceNumber, int& iIndex_face, int& jIndex_face)
{

	Face fc = HalfEdge_Mesh.faces[FaceNumber - 1];
	int HEdgIndex = HalfEdge_Mesh.Privious_Hedge_finder(&HEdg, &fc)->next;
	int HEdgeIndexInFace = HalfEdge_Mesh.HEdgeIndexInFace(HEdgIndex);
	iIndex_face = iIndex;
	jIndex_face = jIndex;
	if (HEdgeIndexInFace == 2)
	{

		iIndex_face = Splines[HEdg.face - 1].tensor2.size() - jIndex - 1;
		jIndex_face = iIndex;

	}
	if (HEdgeIndexInFace == 3)
	{

		iIndex_face = Splines[HEdg.face - 1].tensor2.size() - iIndex - 1;
		jIndex_face = Splines[HEdg.face - 1].tensor2[0].size() - jIndex - 1;

	}

	if (HEdgeIndexInFace == 4)
	{

		iIndex_face = jIndex;
		jIndex_face = Splines[HEdg.face - 1].tensor2[0].size() - iIndex - 1;

	}

}


point multipatch::AccessControleVector(HEdge HEdg, int iIndex, int jIndex)
{

	int iIndex_face = iIndex, jIndex_face = jIndex;
	HalfEdgeBasedIndex_To_FaceBasedIndex(HEdg, iIndex, jIndex, HEdg.face, iIndex_face, jIndex_face);
	return AccessControleVector(HEdg.face, iIndex_face,jIndex_face);	
	
}

void multipatch::G0BasisToControlVector()
{
	int ControlVectorSize = ControleVector[0].size();
	this->ControleVector = vector<vector<float>>(0);

	for (int k = 0;k< this->G0Basis.shape1;k++)
	{
		vector<float> V(ControlVectorSize, 0.);
		ControleVector.push_back(V);
	}

	for (int k = 0;k < this->G0Basis.matrixCoefficients.size();k++)
	{
		
		this->ControleVector
			[this->G0Basis.matrixCoefficients[k].iIdx]
		[this->G0Basis.matrixCoefficients[k].jIdx]= G0Basis.matrixCoefficients[k].coef;
	}

}

void multipatch::G1BasisToControlVector()
{
	int ControlVectorSize = ControleVector[0].size();
	this->ControleVector = vector<vector<float>>(0);

	for (int k = 0;k < this->G1Basis.shape1;k++)
	{
		vector<float> V(ControlVectorSize, 0.);
		ControleVector.push_back(V);
	}

	for (int k = 0;k < this->G1Basis.matrixCoefficients.size();k++)
	{

		this->ControleVector
			[this->G1Basis.matrixCoefficients[k].iIdx]
			[this->G1Basis.matrixCoefficients[k].jIdx] = 
			G1Basis.matrixCoefficients[k].coef;
	}
}

void multipatch::RebuildSplinesFromControlVector()
{
	for (int faceIndex = 0;faceIndex < Splines.size();faceIndex++)
	{
		
		int EdgeAxeControlePointsNumber = Splines[faceIndex].BS.controlGridShape[0];
		int OtherAxeControlePointsNumber = Splines[faceIndex].BS.controlGridShape[1];
		for (int i =0; i< EdgeAxeControlePointsNumber;i++)
			for (int j = 0; j < EdgeAxeControlePointsNumber;j++)
			{
					Splines[faceIndex].tensor2[i][j]=
					AccessControleVector(faceIndex+1,i,j);
			}
	}
}



void multipatch::AddQuadFaceControlePoints(Face& f)
{
	HEdge& he = HalfEdge_Mesh.HalfeEdges[f.HEdge - 1];
	for (int HalfEdgeIndexInFace = 1;HalfEdgeIndexInFace <= 4;HalfEdgeIndexInFace++)
		AddAQuarterFaceOfControlePoints(he, HalfEdgeIndexInFace);

	int EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[0];
	int OtherAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];

	if (EdgeAxeControlePointsNumber % 2 == 1 && OtherAxeControlePointsNumber % 2 == 1)
		AddCentralControlePoint(he, EdgeAxeControlePointsNumber, OtherAxeControlePointsNumber);
	//See explanation in figure Doc/CentralControlePointInFace.png

}

void multipatch::AddAQuarterFaceOfControlePoints(HEdge& he, int HalfEdgeIndexInFace // starts with 1
)
{
	int EdgeAxeQuarterLoopCounter = 0;
	int OtherAxeQuarterLoopCounter = 0;
	int signexI = 1, signeyI = 0, signexJ = 0, signeyJ = 1;
	int FirstIndexX = 0;
	int FirstIndexY = 0;
	if (HalfEdgeIndexInFace == 1)
	{
		//nothing to do
	}
	else if (HalfEdgeIndexInFace == 2)
	{
		signexJ = -1;
		FirstIndexX = Splines[he.face - 1].tensor2.size() - 1;
		FirstIndexY = 0;
		signeyI = 1;
		signexI = 0;
		signeyJ = 0;
	}
	else if (HalfEdgeIndexInFace == 3)
	{
		signexJ = -0;
		FirstIndexX = Splines[he.face - 1].tensor2.size() - 1;
		FirstIndexY = Splines[he.face - 1].tensor2[0].size() - 1;
		signeyI = -0;
		signexI = -1;
		signeyJ = -1;
	}
	else if (HalfEdgeIndexInFace == 4)
	{
		signexJ = 1;
		FirstIndexX = 0;
		FirstIndexY = Splines[he.face - 1].tensor2[0].size() - 1;
		signeyI = -1;
		signexI = 0;
		signeyJ = 0;
	}
	ComputeQuarterLoopCounters(EdgeAxeQuarterLoopCounter, OtherAxeQuarterLoopCounter, he, HalfEdgeIndexInFace);
	for (int j = 0;j < OtherAxeQuarterLoopCounter;j++)
		for (int i = 0;i < EdgeAxeQuarterLoopCounter;i++)
		{
			int FirstTensorIndex = 0;
			int SecondTensorIndex = 0;
			for (int IndexCoordinate = 0;IndexCoordinate < Splines[he.face - 1].AmbiantDimension;IndexCoordinate++)
			{
				FirstTensorIndex = FirstIndexX + signexI * i + signexJ * j;
				SecondTensorIndex = FirstIndexY + signeyI * i + signeyJ * j;
				ControleVector[IndexCoordinate].
					push_back(
						Splines[he.face - 1].
						tensor2[FirstTensorIndex][SecondTensorIndex].
						getCoordinate(IndexCoordinate));
			}
			SecondTensorIndex = 1;
		}
}

void multipatch::ComputeQuarterLoopCounters(int& EdgeAxeLoopCounter, int& OtherAxeLoopCounter,
	HEdge& he, int HalfEdgeIndexInFace)
{
	int EdgeAxeControlePointsNumber;
	int OtherAxeControlePointsNumber;
	if (HalfEdgeIndexInFace == 1 || HalfEdgeIndexInFace == 3)
	{
		EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[0];
		OtherAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];
	}
	else
	{
		EdgeAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[1];
		OtherAxeControlePointsNumber = Splines[he.face - 1].BS.controlGridShape[0];
	}

	if (EdgeAxeControlePointsNumber % 2 == 0)
	{
		EdgeAxeLoopCounter = EdgeAxeControlePointsNumber / 2;
	}
	else
	{
		EdgeAxeLoopCounter = static_cast<int>(std::floor(EdgeAxeControlePointsNumber / 2) + 1);
	}
	if (OtherAxeControlePointsNumber % 2 == 0)
	{
		OtherAxeLoopCounter = OtherAxeControlePointsNumber / 2;
	}
	else
	{
		OtherAxeLoopCounter = static_cast<int>(std::floor(OtherAxeControlePointsNumber / 2));
	}
}

void multipatch::AddCentralControlePoint(HEdge& he, int EdgeAxeControlePointsNumber, int OtherAxeControlePointsNumber)
{
	int i = static_cast<int>(std::floor(EdgeAxeControlePointsNumber / 2));
	int j = static_cast<int>(std::floor(OtherAxeControlePointsNumber / 2));
	for (int k = 0;k < Splines[he.face - 1].AmbiantDimension;k++)
		ControleVector[k].push_back(Splines[he.face - 1].tensor2[i][j].getCoordinate(k));

}