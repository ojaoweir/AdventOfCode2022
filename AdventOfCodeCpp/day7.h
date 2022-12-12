#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <list>
#include <vector>
#include "day7.h"
#include "FileReader.h"
#include "StringUtils.h"

using namespace std;

class day7
{
	class hiearchiFile
	{
		int size = 0;
		std::string name;
	public:
		hiearchiFile(std::string line) {
			std::vector<std::string> strings = StringUtils::split(line, ' ');
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
			std::cout << "\n";
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

			if (dirSize <= threshold) {
				*totalSize += dirSize;
			}

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

	static std::vector<std::string> toVector(std::list<std::string> list) {
		std::vector<std::string> vector;
		for (std::string& str : list)
		{
			vector.push_back(str);
		}
		return vector;
	}
public:
	static void Run() {
		hiearchiDirectory root("/");
		hiearchiDirectory* current = &root;

		std::vector<std::string> linesVector = FileReader::ReadFile("ass7.txt");

		for (int i = 0; i < linesVector.size(); i++) {
			std::string line = linesVector[i];
			std::vector<std::string> commandLine = StringUtils::split(line, ' ');

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
				while (i < linesVector.size() - 1 && linesVector[i].front() != '$') {
					line = linesVector[i];
					std::vector<std::string> tempCommandLine = StringUtils::split(line, ' ');
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
		}

		int totalSize = 0;
		int storageUsed = root.calculateSize(&totalSize, 100000);
		root.print(" ");
		int totalSizeOnDisk = 70000000;
		int storageRequired = 30000000;
		int minSize = storageRequired - (totalSizeOnDisk - storageUsed);
		int smallest = root.calculateSize(0, 0);
		root.findSmallestForRequirement(&smallest, minSize);
		std::cout << endl << "Total Size: " << totalSize << " task2: " << smallest << endl;
	}
};

