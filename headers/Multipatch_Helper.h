
#pragma once

#include "HalfeEdge.h"
#include"splineFunctions.h"


int WhichIndexInCtrVector(int WchQuarter, int iIndex, int jIndex, vector<vector<unsigned>> QuartersDimensions,
	int EdgeAxeControlePointsNumber, int OtherAxeControlePointsNumber);

int whichQuarter(vector<vector<unsigned>>& QuartersDimensions, int iIndex, int jIndex,
		int EdgeAxeControlePointsNumber, int OtherAxeControlePointsNumber);

void ComputeQuartersDimensions(vector<vector<unsigned>>& QuartersDimensions, int face, int EdgeAxeControlePointsNumber,
	int OtherAxeControlePointsNumber);

vector<float> CoordinateChange_PatchParameter(vector<float> EdgeReferenced_Param,int face_MainHEdge_Index);

float SinFct(float x, float y);
