#include "pch.h"
#include<cmath>
#include"Example.h"
#include "MultiPatch.h"
#include "HalfeEdge.h"
#include "Multipatch_Helper.h"


void ComputeQuartersDimensions(vector<vector<unsigned>>& QuartersDimensions
	, int face //this variable is to be omitted
	,int EdgeAxeControlePointsNumber,
	int OtherAxeControlePointsNumber)
{

	if (EdgeAxeControlePointsNumber % 2 == 0 && OtherAxeControlePointsNumber % 2 == 0)
	{
		QuartersDimensions.push_back(
			vector<unsigned>({ static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
			,static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
				}));

		QuartersDimensions.push_back(
			vector<unsigned>({ static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
			,static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
				}));

		QuartersDimensions.push_back(
			vector<unsigned>({ static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
			,static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
				}));

		QuartersDimensions.push_back(
			vector<unsigned>({ static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
			,static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
				}));

	}

	if (EdgeAxeControlePointsNumber % 2 == 1 && OtherAxeControlePointsNumber % 2 == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			QuartersDimensions.push_back(
				vector<unsigned>({ static_cast<unsigned>(EdgeAxeControlePointsNumber / 2) + 1
				,static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
					}));
			QuartersDimensions.push_back(
				vector<unsigned>({ static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
				,static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
					}));
		}

	}
	if (EdgeAxeControlePointsNumber % 2 == 0 && OtherAxeControlePointsNumber % 2 == 1)
	{

		for (int i = 0; i < 2; i++)
		{
			QuartersDimensions.push_back(
				vector<unsigned>({ static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
				,static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
					}));
			QuartersDimensions.push_back(
				vector<unsigned>({ static_cast<unsigned>(OtherAxeControlePointsNumber / 2) + 1
				,static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
					}));
		}
	}

	if (EdgeAxeControlePointsNumber % 2 == 1 && OtherAxeControlePointsNumber % 2 == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			QuartersDimensions.push_back(
				vector<unsigned>({ static_cast<unsigned>(EdgeAxeControlePointsNumber / 2) + 1
				,static_cast<unsigned>(OtherAxeControlePointsNumber / 2)
					}));

			QuartersDimensions.push_back(
				vector<unsigned>({ static_cast<unsigned>(OtherAxeControlePointsNumber / 2) + 1
				,static_cast<unsigned>(EdgeAxeControlePointsNumber / 2)
					}));

		}
	}
}

int whichQuarter(vector<vector<unsigned>>& QuartersDimensions, int iIndex, int jIndex,
	int EdgeAxeControlePointsNumber, int OtherAxeControlePointsNumber)
{
	if (EdgeAxeControlePointsNumber % 2 == 0 && OtherAxeControlePointsNumber % 2 == 0)
	{
		if (iIndex < QuartersDimensions[0][0] && jIndex < QuartersDimensions[0][1])
		{
			return 1;
		}
		else if (iIndex >= QuartersDimensions[0][0] && jIndex < QuartersDimensions[0][1])
		{
			return 2;
		}
		else if (iIndex >= QuartersDimensions[0][0] && jIndex >= QuartersDimensions[0][1]) {
			return 3;
		}
		else if (iIndex < QuartersDimensions[0][0] && jIndex >= QuartersDimensions[0][1]) {
			return 4;
		}

	}

	if (EdgeAxeControlePointsNumber % 2 == 1 && OtherAxeControlePointsNumber % 2 == 0)
	{
		if (iIndex < QuartersDimensions[0][0] && jIndex < QuartersDimensions[0][1])
		{
			return 1;
		}
		else if (iIndex >= QuartersDimensions[0][0] && jIndex < QuartersDimensions[0][1])
		{
			return 2;
		}
		else if (iIndex >= QuartersDimensions[0][0]-1 && jIndex >= QuartersDimensions[0][1]) {
			return 3;
		}
		else if (iIndex < QuartersDimensions[0][0] - 1 && jIndex >= QuartersDimensions[0][1]) {
			return 4;
		}
	}
	if (EdgeAxeControlePointsNumber % 2 == 0 && OtherAxeControlePointsNumber % 2 == 1)
	{
		if (iIndex < QuartersDimensions[0][0] && jIndex < QuartersDimensions[0][1])
		{
			return 1;
		}
		else if (iIndex >= QuartersDimensions[0][0] && jIndex <= QuartersDimensions[0][1])
		{
			return 2;
		}
		else if (iIndex >= QuartersDimensions[0][0] && jIndex > QuartersDimensions[0][1]) {
			return 3;
		}
		else if (iIndex <= QuartersDimensions[0][0] - 1 && jIndex >= QuartersDimensions[0][1]) {
			return 4;
		}
	}
	if (EdgeAxeControlePointsNumber % 2 == 1 && OtherAxeControlePointsNumber % 2 == 1)
	{
		if (iIndex < QuartersDimensions[0][0] && jIndex < QuartersDimensions[0][1])
		{
			return 1;
		}
		else if (iIndex >= QuartersDimensions[0][0] && jIndex <= QuartersDimensions[0][1])
		{
			return 2;
		}
		else if (iIndex >= QuartersDimensions[0][0]-1 && jIndex > QuartersDimensions[0][1])
		{
			return 3;
		}
		else if (iIndex < QuartersDimensions[0][0]-1  && jIndex >= QuartersDimensions[0][1]) {
			return 4;
		}
		else
		{
			return 5;
			//central controle point
		}
	}
	return 0;
}

int WhichIndexInCtrVector(int WchQuarter, int iIndex, int jIndex, vector<vector<unsigned>> QuartersDimensions,
	int EdgeAxeControlePointsNumber, int OtherAxeControlePointsNumber)
{
	int PrevQuartCtrPtsCount = 0;



	if (WchQuarter == 5) {
		return EdgeAxeControlePointsNumber * OtherAxeControlePointsNumber-1;
	}
	else if (WchQuarter == 1) {
		return jIndex * QuartersDimensions[0][0] + iIndex;
	}
	else if (WchQuarter == 2) {
		PrevQuartCtrPtsCount += QuartersDimensions[0][1]* QuartersDimensions[0][0];
		int iQuarterIndex=jIndex;
		int jQuarterIndex= EdgeAxeControlePointsNumber- iIndex-1;
		return PrevQuartCtrPtsCount + jQuarterIndex * QuartersDimensions[1][0] + iQuarterIndex;
	}
	else if (WchQuarter == 3) {
		PrevQuartCtrPtsCount += QuartersDimensions[0][1] * QuartersDimensions[0][0]
			+ QuartersDimensions[1][1] * QuartersDimensions[1][0];
		int iQuarterIndex = EdgeAxeControlePointsNumber - iIndex - 1;
		int jQuarterIndex = OtherAxeControlePointsNumber - jIndex - 1;
		return PrevQuartCtrPtsCount + jQuarterIndex * QuartersDimensions[2][0] + iQuarterIndex;
	}
	else if (WchQuarter == 4) {
		PrevQuartCtrPtsCount += QuartersDimensions[0][1] * QuartersDimensions[0][0]
			+ QuartersDimensions[1][1] * QuartersDimensions[1][0]
		+ QuartersDimensions[2][1] * QuartersDimensions[2][0];
		int iQuarterIndex = OtherAxeControlePointsNumber - jIndex - 1;
		int jQuarterIndex = iIndex ;
		return PrevQuartCtrPtsCount + jQuarterIndex * QuartersDimensions[3][0] + iQuarterIndex;
	}

	return -1;
}


vector<float> CoordinateChange_PatchParameter(vector<float> EdgeReferenced_Param, int HEdge_Index)
{
	vector<float> FaceReferenced_Param(EdgeReferenced_Param);
	if (HEdge_Index ==1)
		return EdgeReferenced_Param;
	else if (HEdge_Index == 2)
	{
		FaceReferenced_Param [1]=EdgeReferenced_Param[0];
		FaceReferenced_Param[0]=1- EdgeReferenced_Param[1];
		

		return FaceReferenced_Param;
	}
	else if (HEdge_Index == 3) {
		FaceReferenced_Param[1] = 1-EdgeReferenced_Param[1];
		FaceReferenced_Param[0] = 1 - EdgeReferenced_Param[0];


		return FaceReferenced_Param;
	}
	else if (HEdge_Index == 4)
	{
		FaceReferenced_Param[1] = 1 - EdgeReferenced_Param[0];
		FaceReferenced_Param[0] = EdgeReferenced_Param[1];


		return FaceReferenced_Param;
	}
}
float SinFct(float x, float y)
{
	return  x * y * sin(x + y);
}