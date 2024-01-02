#pragma once

#include <vector>
#include "splineFunctions.h"
#include"point.h"
namespace knotInsertion {
	void knotInsert(vector<point>& controlePoints, vector<float>& knots,
		int degree, float additionalKnot);

	void knotInsert(vector<point>& controlePoints, vector<float>& knots,
		int degree, float knotToInsert, int intervalIndex);

	void knotInsert(vector<vector<point>>& controlePoints, vector< vector<float>>& knots,
		int degree,	float knotToInsert, int axeOfInsertion);

	void Axe0knotInsertion(vector<vector<point>>& controlePoints, vector< vector<float>>& knots,
		int degree, float knotToInsert, int axeOfInsertion, int intervalIndex);

	void Axe1knotInsertion(vector<vector<point>>& controlePoints, vector< vector<float>>& knots,
		int degree, float knotToInsert, int axeOfInsertion, int intervalIndex);

	void computeASingleNewControlePoint_knotInsertion(point& Q, int i, vector<point>& controlePoints,
		vector<float>& knots, int degree, float knotToInsert, int intervalIndex);
}
