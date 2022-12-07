// AdventOfCodeCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <list>



int len(std::string str)
{
	int length = 1;
	for (int i = 0; str[i] != '\0'; i++)
	{
		length++;

	}
	return length;
}

std::list<std::string> split(std::string str, char seperator)
{
	int currIndex = 0, i = 0;
	int startIndex = 0, endIndex = 0;
	std::list<std::string> strings;

	for (int i = 0; i < len(str); i++) {
		if (str[i] == seperator || i == len(str))
		{
			endIndex = i;
			std::string subStr = "";
			subStr.append(str, startIndex, endIndex - startIndex);
			if (subStr != "$") {
				strings.push_back(subStr);
			}
			startIndex = endIndex + 1;
		}
	}
	std::string subStr = "";
	subStr.append(str, startIndex, endIndex - startIndex);
	strings.push_back(subStr);
	return strings;
}

class hiearchiFile
{
	int size = 0;
	std::string name;
public:
	hiearchiFile(std::string line) {
		std::list<std::string> strings = split(line, ' ');
		size = std::stoi(strings.front());
		name = strings.back();

		std::cout << name << " : " << size << "\n";
	}
};

class hiearchiDirectory
{
private:
	std::string name;
	std::list<hiearchiFile> files;
	std::list<hiearchiDirectory> subDirectories;
	hiearchiDirectory *parentDirectory;

public:
	hiearchiDirectory(std::string name) {
		this->name = name;
	}

	hiearchiDirectory(std::string name, hiearchiDirectory *parentDirectory) {
		this->name = name;
		this->parentDirectory = parentDirectory;
	}

	void addFile(hiearchiFile file) {
		files.push_back(file);
	}
	void addDirectory(hiearchiDirectory directory) {
		subDirectories.push_back(directory);
	}
};


int main()
{
	std::ifstream readFile;
	readFile.open("ass7.txt");
	std::list<std::string> LinesList2;
	hiearchiDirectory root("/");
	hiearchiDirectory current = root;

	//read input
	while (readFile) {
		std::string myString;
		std::getline(readFile, myString);
		LinesList2.push_back(myString);
	}

	for (std::string& str : LinesList2)
	{
		std::cout << str << std::endl;
	}

	for (std::string& str : LinesList2)
	{
		std::list<std::string> commandLine = split(str, ' ');
		std::string command;
		command = commandLine.front();
		//switchcase på command
	}

	hiearchiFile t("11968 pcccp");

	//if (readFile.is_open()) {
	//	std::string myString;
	//	std::getline(readFile, myString);
	//	//readFile >> myString;
	//	std::cout << myString;
	//}
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
