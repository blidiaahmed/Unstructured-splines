#include "pch.h"

#include "png/CImg/CImg.h"

#include"OBJMesh.h"



//  Important !!!!!!!!!!!!!!!
// use the following site
// https://fr-fr.topographic-map.com/map-nd3q/Alg%C3%A9rie/?center=28.0332%2C4.57031
//at the end of the page there is the api


//ocean maps
//https://ec.europa.eu/maritimeaffairs/atlas/maritime_atlas/#lang=EN;p=w;bkgd=5;theme=7:0.5;c=-1221470.506399002,6886553.123939512;z=4

//wind maps
//https://www.windy.com/?36.527,-87.012,3
TEST(Examples, AltitudeExample)
{

	OBJMesh Om;
	//prepare the image
	string str = "../models/CarteAltitude.bmp";

	// The Following is a time consuming part
	// You can execute it whene needed
	//PngToPointCloud(str, Om);
	//WriteOBJ("../models/test.obj", Om);
	//system("meshlab models/test.obj");
	float Error = 1;
	EXPECT_NEAR(Error, 0, 0.01);
}

