#include <iostream>
#include <fstream>
#pragma once
#include"OBJMesh.h"
#include "string"
point parseVertices(vector<string>& seglist);
vector<int> parseFaces(vector<string> seglist);
OBJMesh ReadObj(string str);
