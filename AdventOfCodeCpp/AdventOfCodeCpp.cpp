// AdventOfCodeCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <list>
#include <vector>



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
	}

	void print(std::string indentation) {
		std::cout << indentation << "- " << name << " (file, size=" << size << ")\n";
	}

	int getSize() {
		return size;
	}
};

class hiearchiDirectory
{
public:
	std::string name;
	hiearchiDirectory* parentDirectory;
	std::vector<hiearchiFile> files;
	std::vector<hiearchiDirectory> subDirectories;
	int size = 0;

	hiearchiDirectory(std::string name) {
		this->name = name;
	}

	hiearchiDirectory(std::string name, hiearchiDirectory* parentDirectory) {
		this->name = name;
		this->parentDirectory = parentDirectory;
	}

	hiearchiDirectory* getSub(std::string name) {
		for (int i = 0; i < subDirectories.size(); i++) {
			if (subDirectories[i].name == name) {
				return &subDirectories[i];
			}
		}
	}

	void addSub(hiearchiDirectory newDir) {
		subDirectories.push_back(newDir);
	}
	void addSub(std::string newName) {
		hiearchiDirectory dir(newName, this);
		subDirectories.push_back(dir);
	}

	void print(std::string indentation) {
		std::cout << indentation;
		std::cout << "- ";
		std::cout << name;
		std::cout << " (/dir) :parent ";
		if (parentDirectory) {
			std::cout << parentDirectory->name;
		}
		else {
			std::cout << "null";
		}
		std::cout<< "\n";
		if (subDirectories.size() > 0) {
			for (hiearchiDirectory dir : subDirectories) {
				dir.print(indentation + "   ");
			}
		}
		if (files.size() > 0) {
			for (hiearchiFile file : files) {
				file.print(indentation + "   ");
			}
		}
	}

	int calculateSize(int* totalSize, int threshold) {
		if (size != 0) {
			return size;
		}
		int dirSize = 0;
		for (int i = 0; i < subDirectories.size(); i++) {
			dirSize += subDirectories[i].calculateSize(totalSize, threshold);
		}
		for (int i = 0; i < files.size(); i++) {
			dirSize += files[i].getSize();
		}

		//std::cout << "DirSize: " << dirSize << " Threshold: " << threshold << " compare: " << (dirSize <= threshold) << " Total: " << *totalSize << std::endl;
		if (dirSize <= threshold) {
			*totalSize += dirSize;
		}
		std::cout << name << ": " << dirSize << std::endl;
		size = dirSize;
		return size;
	}

	void findSmallestForRequirement(int* smallest, int requirement) {
		int temp = 0;
		int threshold = 0;
		if (calculateSize(&temp, threshold) < *smallest && size >= requirement) {
			*smallest = size;
		}
		for (int i = 0; i < subDirectories.size(); i++) {
			subDirectories[i].findSmallestForRequirement(smallest, requirement);
		}
	}
};

std::vector<std::string> toVector(std::list<std::string> list) {
	std::vector<std::string> vector;
	for(std::string& str : list)
	{
		vector.push_back(str);
	}
	return vector;
}

int main()
{
	std::ifstream readFile;
	readFile.open("ass7.txt");
	std::list<std::string> LinesList2;
	hiearchiDirectory root("/");
	hiearchiDirectory* current = &root;

	//read input
	while (readFile) {
		std::string myString;
		std::getline(readFile, myString);
		LinesList2.push_back(myString);
	}
	readFile.close();

	std::vector<std::string> linesVector = toVector(LinesList2);

	for (int i = 0; i < linesVector.size(); i++) {
		std::string line = linesVector[i];
		std::list<std::string> commandLine = split(line, ' ');

		std::string command;
		command = commandLine.front();
		if (command == "cd") {
			command = commandLine.back();
			if (command == "/") {
				current = &root;
			}
			else if (command == "..") {
				current = current->parentDirectory;
			}
			else {
				current = current->getSub(command);
			}
		}
		else {
			i++;
			while (i < linesVector.size()-1 && linesVector[i].front() != '$') {
				line = linesVector[i];
				std::list<std::string> tempCommandLine = split(line, ' ');
				if (tempCommandLine.front() == "dir") {
					hiearchiDirectory dir(tempCommandLine.back(), current);
					current->addSub(tempCommandLine.back());
				}
				else {
					hiearchiFile file(linesVector[i]);
					current->files.push_back(file);
				}
				i++;
			}
			i--;
		}

		//std::cout << linesVector[i] << "\n";
		//current->print(" ");
		//std::cout << "\n";
		//root.print(" ");
		//std::cout << "\n ----------------------------------------------------------------------------------------------------- \n";
	}

	int totalSize = 0;
	int storageUsed = root.calculateSize(&totalSize, 100000);
	root.print(" ");
	int totalSizeOnDisk = 70000000;
	int storageRequired = 30000000;
	int minSize = storageRequired - (totalSizeOnDisk - storageUsed);
	int smallest = root.calculateSize(0,0);
	root.findSmallestForRequirement(&smallest, minSize);
	std::cout << "Total Size: " << totalSize << " task2: " << smallest;
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
