#include "Day12.h"
#include "FileReader.h"

#include <vector>
#include <string>

using namespace std;

class Position {
	vector<Position*> neighbors;
	int x;
	int y;
	char height;
	int distanceFromStart = 1000000;
	int distanceFromEnd = -5;

	void DrawPath(int maxX, int maxY, vector<Position> positions) {
		for (int x = 0; x < maxX; x++) {
			for (int y = 0; y < maxY; y++) {
				char c = '.';
				if (x == positions.back().GetX() && y == positions.back().GetY()) {
					c = 'A';
				}
				else {
					for (int i = 0; i < positions.size(); i++) {
						if (positions[i].GetX() == x && positions[i].GetY() == y) {
							c = '*';
							break;
						}
					}
				}
				cout << c;
			}
			cout << endl;
		}
	}

public:
	Position(char height, int x, int y) {
		this->x = x;
		this->y = y;
		this->height = height;

	}

	void AddNeighbor(Position* neighbor) {
		neighbors.push_back(neighbor);
	}

	int GetX() {
		return x;
	}

	int GetY() {
		return y;
	}

	char GetHeight() {
		return height;
	}

	int FindGoal(Position* goal, int numberOfSteps, int maxX, int maxY, vector<Position> passedPos) {
		cout << "Number of steps: " << numberOfSteps << " current: " << x << ":" << y << " Goal: " << goal->GetX() << ":" << goal->GetY() << endl;
		passedPos.push_back(*this);
		DrawPath(maxX, maxY, passedPos);
		//for (int x = 0; x < maxX; x++) {
		//	for (int y = 0; y < maxY; y++) {
		//		char c = '.';
		//		if (x == this->x && y == this->y) {
		//			c = 'A';
		//		}
		//		else {
		//			for (int i = 0; i < passedPos.size(); i++) {
		//				if (passedPos[i].GetX() == x && passedPos[i].GetY() == y) {
		//					c = '*';
		//					break;
		//				}
		//			}
		//		}
		//		cout << c;
		//	}
		//	cout << endl;
		//}
		//Goal reached:
//cout << x << " : " << y << endl;

		if (x == goal->x && y == goal->y) {

			//Cases where it is dead:
			if (numberOfSteps < distanceFromStart) {
				distanceFromStart = numberOfSteps;
			}
			distanceFromEnd = 0;
			cout << "X: " << x << " and Y: " << y << " is goal, was reached in " << numberOfSteps << " steps." << endl;
			cout << "Minimum is: " << distanceFromStart << endl << endl;
			return 0;
		}


		//Cases where it is dead:
		if (numberOfSteps >= distanceFromStart) {
			return -1;
		}
		else {
			distanceFromStart = numberOfSteps;
		}

		cout << endl;

		if (neighbors.size() == 0) {
			return -1;
		}

		if (distanceFromEnd == -1) {
			return -1;
		}

		// Search children:
		if (distanceFromEnd = -5) {
			for (int i = 0; i < neighbors.size(); i++) {
				int childDistanceToGoal = neighbors[i]->FindGoal(goal, distanceFromStart + 1, maxX, maxY, passedPos);
				if (childDistanceToGoal == -1) {
					continue;
				}

				if (distanceFromEnd == -5 || childDistanceToGoal + 1 < distanceFromEnd) {
					distanceFromEnd = childDistanceToGoal + 1;
				}
			}

			//If no child finds goal, kill node
			if (distanceFromEnd == -5) {
				distanceFromEnd = -1;
			}
		}

		cout << "Goal reached in " << distanceFromStart + distanceFromEnd << " steps:" << endl;

		return distanceFromEnd;
	}

	void SetHeighToLower() {
		height = tolower(height);
	}
};

Position* FindPosition(vector<Position>* positions, int targetX, int targetY) {
	for (int i = 0; i < positions->size(); i++) {
		if (positions->at(i).GetX() == targetX && positions->at(i).GetY() == targetY) {
			return &positions->at(i);
		}
	}
	return NULL;
}


void Day12::Run() {
	vector<string> lines = FileReader::ReadFile("ass12.txt");
	lines.pop_back();

	vector<Position> allPositions;

	int gridX = lines.size();
	int gridY = lines[0].size();

	Position* start = NULL;
	Position* goal = NULL;

	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++) {
			char height = lines[x].at(y);
			allPositions.push_back(Position(height, x, y));
		}
	}

	for (int i = 0; i < allPositions.size(); i++) {
		if (allPositions[i].GetHeight() == 'S') {
			start = &allPositions[i];
			start->SetHeighToLower();
		}
		if (allPositions[i].GetHeight() == 'E') {
			goal = &allPositions[i];
			goal->SetHeighToLower();
		}
	}

	for (int i = 0; i < allPositions.size(); i++) {
		Position* currentPosition = &allPositions[i];
		for (int x = currentPosition->GetX() - 1; x <= currentPosition->GetX() + 1; x += 2) {
			Position* ptr = FindPosition(&allPositions, x, currentPosition->GetY());
			if (ptr != NULL) {
				if (ptr->GetHeight() <= currentPosition->GetHeight() + 1) {
					currentPosition->AddNeighbor(ptr);
				}
			}
		}
		for (int y = currentPosition->GetY() - 1; y <= currentPosition->GetY() + 1; y += 2) {
			Position* ptr = FindPosition(&allPositions, currentPosition->GetX(), y);
			if (ptr != NULL) {
				if (ptr->GetHeight() <= currentPosition->GetHeight() + 1) {
					currentPosition->AddNeighbor(ptr);
				}
			}
		}
	}

	if (start != NULL && goal != NULL) {
		vector<Position> passedPos;
		cout << "Task1: " << start->FindGoal(goal, 0, gridX, gridY, passedPos);
	}
}