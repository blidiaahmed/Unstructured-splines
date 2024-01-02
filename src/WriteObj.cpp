#include"pch.h"
#include"WriteObj.h"

void WriteOBJ(std::string str, OBJMesh Om)
{
	ofstream myfile;
	myfile.open(str);
	for (point pt : Om.points)
	{
		int dim = pt.getDimension();
		myfile << "v ";
		myfile << pt.getCoordinate(0) << " ";
		myfile << pt.getCoordinate(1) << " ";
		myfile << pt.getCoordinate(2) << endl;
		if (dim == 6) {
			myfile << "vn ";
			myfile << pt.getCoordinate(3) << " ";
			myfile << pt.getCoordinate(4) << " ";
			myfile << pt.getCoordinate(5) << endl;
		}
		if (dim > 6) {
			myfile << "vt ";
			myfile << pt.getCoordinate(6) << " ";
			myfile << pt.getCoordinate(7) << " ";
			myfile << pt.getCoordinate(8) << endl;
		}
	}

	for (vector< int> f : Om.faces)
	{
		myfile << "f ";

		for (int i = 0; i < f.size();i++)
			myfile << f[i] << " ";

		myfile << endl;
	}
	myfile.close();
}