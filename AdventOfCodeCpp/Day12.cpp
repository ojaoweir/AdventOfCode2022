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

	void DrawPath(int maxX, int maxY, vector<Position>* positions) {
		return;
		for (int x = 0; x < maxX; x++) {
			for (int y = 0; y < maxY; y++) {
				char c = '.';
				if (x == positions->back().GetX() && y == positions->back().GetY()) {
					c = 'A';
				}
				else {
					for (int i = 0; i < positions->size(); i++) {
						if (positions->at(i).GetX() == x && positions->at(i).GetY() == y) {
							c =positions->at(i).GetHeight();
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

	int f;
	int g;
	int h;

	void SetHeight(char c) {
		height = c;
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

	vector<Position> FindGoal(Position* goal, int numberOfSteps, int maxX, int maxY, vector<Position>* passedPos) {
		//cout << "Number of steps: " << numberOfSteps << " current: " << x << ":" << y << " Goal: " << goal->GetX() << ":" << goal->GetY() << endl;
		passedPos->push_back(*this);
		DrawPath(maxX, maxY, passedPos);

		vector<Position> pathToEnd;
		if (x == goal->x && y == goal->y) {

			//Cases where it is dead:
			if (passedPos->size() < distanceFromStart) {
				distanceFromStart = passedPos->size();
			}
			distanceFromEnd = 0;
			//cout << "X: " << x << " and Y: " << y << " is goal, was reached in " << numberOfSteps << " steps." << endl;
			//cout << "Minimum is: " << distanceFromStart << endl << endl;
			pathToEnd.push_back(*this);
			passedPos->pop_back();
			return pathToEnd;
			//return 0;
		}


		//Cases where it is dead:
		if (numberOfSteps >= distanceFromStart) {
			passedPos->pop_back();
			return pathToEnd;
			//return -1;
		}
		else {
			distanceFromStart = passedPos->size();
		}

		//cout << endl;

		if (neighbors.size() == 0) {
			passedPos->pop_back();
			return pathToEnd;
			//return -1;
		}

		if (distanceFromEnd == -1) {
			passedPos->pop_back();
			return pathToEnd;
			//return -1;
		}

		// Search children:
		if (distanceFromEnd = -5) {
			for (int i = 0; i < neighbors.size(); i++) {
				vector<Position> childPathToEnd = neighbors[i]->FindGoal(goal, distanceFromStart + 1, maxX, maxY, passedPos);
				if (childPathToEnd.empty()) {
					continue;
				}
				//int childDistanceToGoal = neighbors[i]->FindGoal(goal, distanceFromStart + 1, maxX, maxY, passedPos);
				//if (childDistanceToGoal == -1) {
				//	continue;
				//}

				if (distanceFromEnd == -5 || childPathToEnd.size() < distanceFromEnd) {
					pathToEnd = childPathToEnd;
					distanceFromEnd = pathToEnd.size();
				}
			}

			//If no child finds goal, kill node
			if (distanceFromEnd == -5) {
				passedPos->pop_back();
				distanceFromEnd = -1;
				vector<Position> t;
				return t;
			}
		}

		vector<Position> temp;
		for (int i = 0; i < pathToEnd.size(); i++) {
			temp.push_back(pathToEnd[i]);
		}
		for (int i = 0; i < passedPos->size(); i++) {
			temp.push_back(passedPos->at(i));
		}
		//cout << "Goal reached in " << distanceFromStart + distanceFromEnd << " steps:" << endl;
		//cout << "Goal reached in " << temp.size() << " steps:" << endl;
		DrawPath(maxX, maxY, &temp);
		//cout << endl;

		pathToEnd.push_back(*this);
		passedPos->pop_back();
		return pathToEnd;
		//return distanceFromEnd;
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


class AStarCoordinate {
public:
	int x;
	int y;
	AStarCoordinate* parent;
	int parentIndex;
	int f;
	int g;
	int h;
	char height;

	AStarCoordinate() {};
	AStarCoordinate(int x, int y, AStarCoordinate* parent, char height, int parentIndex) {
		this->x = x;
		this->y = y;
		this->parent = parent;
		if (height == 'E') {
			height = 'z';
		}
		this->height = height;
		this->parentIndex = parentIndex;
	}

	void Copy(AStarCoordinate other) {
		parentIndex = other.parentIndex;
		f = other.f;
		g = other.g;
		h = other.h;
	}
};



void DrawAStarPath(int maxX, int maxY, vector<AStarCoordinate>* positions) {
	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			char c = '.';
			if (x == positions->back().x && y == positions->back().y) {
				c = 'A';
			}
			else {
				for (int i = 0; i < positions->size(); i++) {
					if (positions->at(i).x == x && positions->at(i).y == y) {
						c = positions->at(i).height;
						break;
					}
				}
			}
			cout << c;
		}
		cout << endl;
	}
	cout <<endl << "--------------------------------------------------------------" << endl;
}

void PrintSuccessorTree(AStarCoordinate* parent, AStarCoordinate* current, vector<AStarCoordinate>* closed) {
	if (current->parentIndex == -1 || closed->size() == 0) {
		return;
	}
	AStarCoordinate temp = closed->at(current->parentIndex);
	vector<AStarCoordinate> tempVector;
	while (true) {
		tempVector.push_back(temp);
		if (temp.parentIndex != -1) {
			temp = closed->at(temp.parentIndex);
		}
		else {
			break;
		}
	}
	tempVector.push_back(*current);
	//DrawAStarPath(41, 161, &tempVector);
	DrawAStarPath(5, 8, &tempVector);

}


int AStarGenerateSuccessor(int successorX, int successorY, int goalX, int goalY, vector<AStarCoordinate>* open, vector<AStarCoordinate>* closed, AStarCoordinate* q, char height) {
	//d) for each successor

	AStarCoordinate successor(successorX, successorY, q, height, closed->size()-1);
	if (successor.height > q->height + 1) {
		return -1;
	}
	//PrintSuccessorTree(q, &successor, closed);

	//i) if successor is the goal, stop search
	if (successor.x == goalX && successor.y == goalY) {
		return q->g + 1;
		//finished 
	}

	/*else, compute both gand h for successor
		successor.g = q.g + distance between
		successor and q
		successor.h = distance from goal to
		successor*/
	int diffX = goalX > successor.x ? goalX - successor.x : successor.x - goalX;
	int diffY = goalY > successor.y ? goalY - successor.y : successor.y - goalY;
	
	successor.g = q->g + 1;
	successor.h = (diffX + diffY) / 2;
	//successor.h = 'z' - successor.height * (diffX + diffY);
	successor.f = successor.g + successor.h;

	/*iii) if a node with the same position as
	successor is in the OPEN list which has a
		lower f than successor, skip this successor*/
	bool skipSuccessor = false;
	for (int i = 0; i < open->size(); i++) {
		if (open->at(i).x == successor.x && open->at(i).y == successor.y) {
			if (open->at(i).f <= successor.f) {
				skipSuccessor = true;
				break;
			}
			else {
				open->at(i).Copy(successor);
				skipSuccessor = true;
				break;
			}
		}
	}
	//iV) if a node with the same position as
	//successor  is in the CLOSED list which has
	//	a lower f than successor, skip this successor
	//	otherwise, add  the node to the open list
	//	end(for loop)
	for (int i = 0; i < closed->size(); i++) {
		if (closed->at(i).x == successor.x && closed->at(i).y == successor.y) {
			if (closed->at(i).f <= successor.f) {
				skipSuccessor = true;
				break;
			}
		}
	}

	if (skipSuccessor) {
		return -1;
	}
	open->push_back(successor);
	return -1;
}


int FindGoalAStar(int gridX, int gridY, int startX, int startY, int endX, int endY, vector<string> lines, int breakAfterMax) {

	// ASTAR::
	//------------------------------------------------------------------
	vector<AStarCoordinate> closed;
	vector<AStarCoordinate> open;

	AStarCoordinate aStarStart(startX, startY, NULL, 'a', -1);
	aStarStart.g = 0;
	aStarStart.f = 0;
	aStarStart.h = 0;
	open.push_back(aStarStart);
	AStarCoordinate q = open.back();
	int goalReached = -1;

	while (!open.empty()) {
		/*a) find the node with the least f on
		the open list, call it "q"*/
		q = open.back();
		if (q.g > breakAfterMax) {
			return breakAfterMax + 1;
		}
		int indexOfLeastF = open.size() - 1;
		for (int i = 0; i < open.size(); i++) {
			if (open[i].f < q.f) {
				q = open[i];
				indexOfLeastF = i;
			}
		}


		//b) pop q off the open list
		open.erase(open.begin() + indexOfLeastF);

		//push q on the closed list
		closed.push_back(q);

		/*c) generate q's 8 successors and set their
		parents to q*/
		for (int i = q.x - 1; i <= q.x + 1; i += 2) {
			if (i < 0 || i >= gridX) {
				continue;
			}
			goalReached = AStarGenerateSuccessor(i, q.y, endX, endY, &open, &closed, &q, lines[i].at(q.y));
			if (goalReached > 0) {
				break;
			}
		}
		if (goalReached > 0) {
			break;
		}
		for (int i = q.y - 1; i <= q.y + 1; i += 2) {
			if (i < 0 || i >= gridY) {
				continue;
			}
			goalReached = AStarGenerateSuccessor(q.x, i, endX, endY, &open, &closed, &q, lines[q.x].at(i));
			if (goalReached > 0) {
				break;
			}
		}
		if (goalReached > 0) {
			break;
		}
	}
	return goalReached;
}


void Task2(int gridX, int gridY, int endX, int endY, vector<string> lines) {
	vector<int> allStartsX;
	vector<int> allStartsY;
	vector<int> allDistances;

	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++) {
			char height = lines[x].at(y);
			if (height == 'S' || height == 'a') {
				allStartsX.push_back(x);
				allStartsY.push_back(y);
			}
		}
	}
	int minDistance = 1000000;

	for (int i = 0; i < allStartsX.size(); i++) {
		
		int temp = FindGoalAStar(gridX, gridY, allStartsX[i], allStartsY[i], endX, endY, lines, minDistance);
		if (temp == -1) {
			continue;
		}
		if (temp < minDistance) {
			minDistance = temp;
		}
	}
	cout << "Task2: Goal is reached in " << minDistance << " steps." << endl << endl;
}
void Task1(int gridX, int gridY, int endX, int endY, vector<string> lines) {
	int startX = -1;
	int startY = -1;
	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++) {
			char height = lines[x].at(y);
			if (height == 'S') {
				startX = x;
				startY = y;
				continue;
			}
		}
	}
	int goalReached = FindGoalAStar(gridX, gridY, startX, startY, endX, endY, lines, 10000000);
	cout << "Task1: Goal is reached in " << goalReached << " steps." << endl;
}

void Day12::Run() {
	vector<string> lines = FileReader::ReadFile("ass12.txt");
	lines.pop_back();

	int gridX = lines.size();
	int gridY = lines[0].size();
	int endX = -1;
	int endY = -1;

	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++) {
			char height = lines[x].at(y);
			if (height == 'E') {
				endX = x;
				endY = y;
				continue;
			}
		}
	}
	Task1(gridX, gridY, endX, endY, lines);
	Task2(gridX, gridY, endX, endY, lines);

}