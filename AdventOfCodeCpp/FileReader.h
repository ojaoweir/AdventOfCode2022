#pragma once

#include <vector>;
#include <string>;
#include <iostream>
#include <fstream>
using namespace std;

class FileReader {
public:
	static vector<string> ReadFile(string fileName) {
		std::ifstream readFile;
		readFile.open(fileName);
		vector<string> lines;

		//read input
		while (readFile) {
			std::string myString;
			std::getline(readFile, myString);
			lines.push_back(myString);
		}
		readFile.close();
		return lines;
	}
};