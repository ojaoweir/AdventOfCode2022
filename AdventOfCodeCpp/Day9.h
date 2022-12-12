#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;

class Day9
{

public:

	static void Run() {
		vector<string> lines = FileReader::ReadFile("ass9.txt");
		for (int i = 0; i < lines.size(); i++) {
			cout << lines[i] << endl;
		}
	}
};

