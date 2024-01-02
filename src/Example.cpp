#include "pch.h"
#include "Example.h"
#include "HalfeEdge.h"
#include"MeshConvert.h"
#include "png/CImg/CImg.h"
#include "splineFunctions.h"
#include "BSpline.h"
using namespace cimg_library;

void PngToPointCloud(string str, OBJMesh& Om)
{

	char  c[50];
	strcpy(c, str.c_str());
	CImg<float> image(c);

	// Image display
	//CImgDisplay main_disp(image);

	//LOOP OVER THE PIXELS
	int h = image.height();
	int w = image.width();
	float maxi = 0;
	for (int i = 0;i < w;i++)
		for (int j = 0;j < h;j++)
		{
			float pixvalR = image(i, j, 0, 0); // read red val at coord 10,10
			maxi = max(maxi, pixvalR);
			float pixvalG = image(i, j, 0, 1); // read green val at coord 10,10
			maxi = max(maxi, pixvalG);
			float pixvalB = image(i, j, 0, 2); // read blue val at coord 10,10
			maxi = max(maxi, pixvalB);
			 //cout << pixvalR << " " << pixvalG << " " << pixvalB << endl;
			Om.points.push_back(point({ (float)i*3 /(w-1)-1,(float)j*3 / (h-1)-1,-pixvalR - pixvalG //+ (pixvalB-300)
				}));
		}
	for (point& pt : Om.points)
		pt.X[2] /= 6*maxi;
}

void Example_SplineMesh(OBJMesh& Om) {
	spline sp(3);
	sp.BS = BSpline(2);
	sp.tensor2 = vector<vector<point>>
	{
		vector<point>{point({ 0,0,1 }), point({ 1,0,1 }), point({ 2,0,1 }), point({ 3,0,1 }) },
			vector<point>{point({ 0,1,1 }), point({ 1,1,1 }), point({ 2,1,1 }) , point({ 3,1,1 }) },
			vector<point>{point({ 0,2,1 }), point({ 1,2,1 }), point({ 2,2,1 }), point({ 3,2,1 })},
	vector<point>{point({ 0,3,1}), point({1,3,1}), point({2,3,1}), point({3,3,1})}
	};

	for (vector<point>& vect : sp.tensor2)
		for (point& pt : vect)
			pt.X[2] = (pt.X[0] + pt.X[1]) * sin(20 * pt.X[1]) * cos(20 * pt.X[0]);

	int precision = 5;
	Om = sp.ProduceOBJMesh(precision);
}


void tensor_example(vector<vector<point>> &tensor)
{
	tensor=vector<vector<point>>
	{
		vector<point>{point({ 0,0,1 }), point({ 1,0,1 }), point({ 2,0,1 }), point({ 3,0,1 }) },
			vector<point>{point({ 0,1,1 }), point({ 1,1,1 }), point({ 2,1,1 }), point({ 3,1,1 }) },
			vector<point>{point({ 0,2,1 }), point({ 1,2,1 }), point({ 2,2,1 }), point({ 3,2,1 })},
			vector<point>{point({ 0,3,1 }), point({ 1,3,1 }), point({ 2,3,1 }), point({ 3,3,1 })}
	};
}

void tensor_example2(vector<vector<point>>& tensor)
{
	tensor = vector<vector<point>>
	{
		vector<point>{point({ 0,0,1 }), point({ 1,0,1 }), point({ 2,0,1 }), point({ 3,0,1 }) },
			vector<point>{point({ 0,1,4 }), point({ 1,1,1 }), point({ 2,1,1 }), point({ 3,1,1 }) },
			vector<point>{point({ 0,2,1 }), point({ 1,2,1 }), point({ 2,2,1 }), point({ 3,2,1 })},
			vector<point>{point({ 0,3,1 }), point({ 1,3,1 }), point({ 2,3,5 }), point({ 3,3,1 })}
	};
}