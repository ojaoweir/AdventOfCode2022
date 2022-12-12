#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;

class coordinate {
	int x;
	int y;

public:
	coordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool Equal(coordinate other) {
		return x == other.x && y == other.y;
	}
};

class coordinateList {
	vector<coordinate> coordinates;

public:
	void Add(int x, int y) {
		coordinate c(x, y);
		for (int i = 0; i < coordinates.size(); i++) {
			if (coordinates[i].Equal(c)) {
				return;
			}
		}
		coordinates.push_back(c);
	}

	int Size() {
		return coordinates.size();
	}
};

class day8
{
	static vector<int> ToIntVector(string* line) {
		vector<int> row;
		for (int i = 0; i < line->size(); i++) {
			string substr = line->substr(i, 1);
			row.push_back(stoi(substr));
		}
		return row;
	}

	static vector<vector<int>> ToIntMatrix(vector<string> lines) {
		vector<vector<int>> matrix;

		for (int i = 0; i < lines.size(); i++) {
			matrix.push_back(ToIntVector(&lines[i]));
		}
		return matrix;
	};

	static void AddTreeViewableForRowFromLeft(coordinateList* coordinates, int rowNumber, vector<int> row) {
		int highest = row.front();
		for (int i = 1; i < row.size(); i++) {
			if (row.at(i) > highest) {
				highest = row.at(i);
				coordinates->Add(rowNumber, i);
				if (highest == 9) {
					return;
				}
			}
		}
	}

	static void AddTreeViewableForRowFromRight(coordinateList* coordinates, int rowNumber, vector<int> row) {
		int highest = row.back();
		for (int i = row.size() - 1; i > 0; i--) {
			if (row.at(i) > highest) {
				highest = row.at(i);
				coordinates->Add(rowNumber, i);
				if (highest == 9) {
					return;
				}
			}
		}
	}

	static void AddTreesViewAbleForColumnFromTop(coordinateList* coordinates, vector<vector<int>>* matrix, int column) {
		int highest = matrix->front()[column];
		for (int i = 1; i < matrix->size(); i++) {
			if (matrix->at(i)[column] > highest) {
				highest = matrix->at(i)[column];
				coordinates->Add(i, column);
				if (highest == 9) {
					return;
				}
			}
		}
	}

	static void AddTreesViewAbleForColumnFromBottom(coordinateList* coordinates, vector<vector<int>>* matrix, int column) {
		int highest = matrix->back()[column];
		for (int i = matrix->size() - 2; i > 0; i--) {
			if (matrix->at(i)[column] > highest) {
				highest = matrix->at(i)[column];
				coordinates->Add(i, column);
				if (highest == 9) {
					return;
				}
			}
		}
	}

	static void AddEdgesAsViewable(coordinateList* coordinates, vector<vector<int>>* matrix) {
		for (int i = 0; i < matrix->front().size(); i++) {
			coordinates->Add(0, i);
		}		
		for (int i = 0; i < matrix->back().size(); i++) {
			coordinates->Add(matrix->size()-1, i);
		}
		for (int i = 1; i < matrix->size() - 1; i++) {
			coordinates->Add(i, 0);
			coordinates->Add(i, matrix->at(i).size()-1);
		}
	}

	static int calculateViewForTree(int x, int y, vector<vector<int>>* matrix) {
		int viewableLeft = 0;
		int viewableRight = 0;
		int viewableDown = 0;
		int viewableUp = 0;

		//Check left
		for (int i = y - 1; i >= 0; i--) {
			viewableLeft++;
			if (matrix->at(x)[i] >= matrix->at(x)[y]) {
				break;
			}
		}

		//Check Right
		for (int i = y + 1; i < matrix->at(x).size(); i++) {
			viewableRight++;
			if (matrix->at(x)[i] >= matrix->at(x)[y]) {
				break;
			}
		}

		//Check Down
		for (int i = x + 1; i < matrix->size(); i++) {
			viewableDown++;
			if (matrix->at(i)[y] >= matrix->at(x)[y]) {
				break;
			}
		}

		//Check Up
		for (int i = x - 1; i >= 0; i--) {
			viewableUp++;
			if (matrix->at(i)[y] >= matrix->at(x)[y]) {
				break;
			}
		}

		return viewableDown * viewableLeft * viewableRight * viewableUp;
	}

public:
	static void Run() {
		vector<string> lines = FileReader::ReadFile("ass8.txt");
		lines.pop_back();
		vector<vector<int>> matrix = ToIntMatrix(lines);
		vector<coordinate> viewableTrees;
		coordinateList coordinates;
		
		int width = matrix[0].size();
		int height = matrix.size();

		AddEdgesAsViewable(&coordinates, &matrix);

		for (int i = 1; i < height-1; i++) {
			AddTreeViewableForRowFromLeft(&coordinates, i, matrix[i]);
			AddTreeViewableForRowFromRight(&coordinates, i, matrix[i]);
		}

		for (int i = 1; i < width - 1; i++) {
			AddTreesViewAbleForColumnFromTop(&coordinates, &matrix, i);
			AddTreesViewAbleForColumnFromBottom(&coordinates, &matrix, i);
		}

		cout << "Task1: " << coordinates.Size() << endl;

		int highestViewScore = 1;
		for (int i = 1; i < matrix.size()-1; i++) {
			for (int j = 1; j < matrix.at(0).size()-1; j++) {
				int score = calculateViewForTree(i, j, &matrix);
				if (score > highestViewScore) {
					highestViewScore = score;
				}
			}
		}
		cout << "Task2: " << highestViewScore << endl;
	}
};

