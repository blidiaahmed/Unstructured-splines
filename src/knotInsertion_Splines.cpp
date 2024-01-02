#include "pch.h"
#include "knotInsertion_Splines.h"
#include"MultiPatch_Helper.h"
namespace knotInsertion {
	void knotInsert(vector<point>& controlePoints, vector<float>& knots, int degree, float knotToInsert)
	{
		int intervalIndex = SelectIntervalIndex(knotToInsert, knots);
		knotInsert(controlePoints, knots, degree, knotToInsert, intervalIndex);
	}

	void knotInsert(vector<point>& controlePoints, vector<float>& knots, int degree, float knotToInsert, int intervalIndex)
	{
		vector<point> newControlepoints;
		for (int i = intervalIndex - degree + 1; i <= intervalIndex; i++)
		{
			point Q;
			computeASingleNewControlePoint_knotInsertion(Q, i,controlePoints,knots,degree,
				knotToInsert,intervalIndex);
			newControlepoints.push_back(Q);
		}

		// copy the new control points
		for (int i = intervalIndex - degree + 1; i < intervalIndex; i++)
			controlePoints[i] = newControlepoints[i - intervalIndex + degree - 1];

		// the last controle point is inserted
		int i = intervalIndex;
		vector<point>::iterator  it_controlePoints = controlePoints.begin();
		controlePoints.insert(it_controlePoints + i, newControlepoints.back());

		vector<float>::iterator  it = knots.begin();
		knots.insert(it + intervalIndex + 1, knotToInsert);
	}


	void knotInsert(vector<vector<point>>& controlePoints, vector< vector<float>>& knots,
		int degree,float knotToInsert, int axeOfInsertion //0 or 1
	)
	{
		int intervalIndex = SelectIntervalIndex(knotToInsert, knots[axeOfInsertion]);
		if (axeOfInsertion == 0)
		{
			Axe0knotInsertion(controlePoints, knots,
				degree,	knotToInsert, axeOfInsertion, intervalIndex);
		}
		if (axeOfInsertion == 1)
		{
			Axe1knotInsertion(controlePoints, knots,
				degree,	knotToInsert, axeOfInsertion, intervalIndex);
		}
	}

	void Axe0knotInsertion(vector<vector<point>>& controlePoints, vector< vector<float>>& knots,
		int degree,	float knotToInsert, int axeOfInsertion, int intervalIndex)
	{
		int consernedAxeSize = controlePoints.size();
		int OtherAxeSize = controlePoints[0].size();

		vector<vector<point>> newTensor;
		for (int i = 0;i < consernedAxeSize + 1;i++)
			newTensor.push_back(vector<point>{});

		vector<point> controlePointsVector_tmp;
		vector<float> copyknots_tmp;
		for (int j = 0; j < OtherAxeSize; j++)
		{
			controlePointsVector_tmp.clear();
			for (int i = 0; i < consernedAxeSize;i++)
				controlePointsVector_tmp.push_back(controlePoints[i][j]);
			copyknots_tmp = knots[axeOfInsertion];
			knotInsert(controlePointsVector_tmp, copyknots_tmp, degree, knotToInsert);

			for (int i = 0; i < consernedAxeSize + 1;i++)
				newTensor[i].push_back(controlePointsVector_tmp[i]);
		}
		controlePoints = newTensor;
		//modify the knot series
		knots[axeOfInsertion] = copyknots_tmp;
	}

	void Axe1knotInsertion(vector<vector<point>>& controlePoints, vector< vector<float>>& knots,
		int degree,	float knotToInsert, int axeOfInsertion, int intervalIndex)
	{
		int OtherAxeSize = controlePoints.size();
		int consernedAxeSize = controlePoints[0].size();

		vector<float> copyknots_tmp;
		
		for (int j = 0; j < OtherAxeSize; j++)
		{
			vector<point>& controlePointsVector_tmp = controlePoints[j];
			copyknots_tmp = knots[axeOfInsertion];
			knotInsert(controlePointsVector_tmp, copyknots_tmp, degree, knotToInsert);
		}
		knots[axeOfInsertion] = copyknots_tmp;
	}
	
	void computeASingleNewControlePoint_knotInsertion(point& Q, int i,
		vector<point>& controlePoints,
		vector<float>& knots, int degree,
		float knotToInsert, int intervalIndex)
	{
		float a = (knotToInsert - knots[i]) / (knots[i + degree] - knots[i]);
		Q = (1 - a) * controlePoints[i - 1] + a * controlePoints[i];

	}
}