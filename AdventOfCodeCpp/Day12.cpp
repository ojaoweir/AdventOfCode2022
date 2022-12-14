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


void AStarGenerateSuccessor(int successorX, int successorY, Position* goal, vector<AStarCoordinate>* open, vector<AStarCoordinate>* closed, AStarCoordinate* q, char height) {
	//d) for each successor

	AStarCoordinate successor(successorX, successorY, q, height, closed->size()-1);
	if (successor.height > q->height + 1) {
		return;
	}
	//PrintSuccessorTree(q, &successor, closed);

	//i) if successor is the goal, stop search
	if (successor.x == goal->GetX() && successor.y == goal->GetY()) {
		cout << "Goal is reached in " << q->g + 1<< " steps." << endl << endl;
		return;
		//finished 
	}

	/*else, compute both gand h for successor
		successor.g = q.g + distance between
		successor and q
		successor.h = distance from goal to
		successor*/
	int diffX = goal->GetX() > successor.x ? goal->GetX() - successor.x : successor.x - goal->GetY();
	int diffY = goal->GetY() > successor.y ? goal->GetY() - successor.y : successor.y - goal->GetY();
	
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
		return;
	}
	open->push_back(successor);
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
			goal->SetHeight('z');
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

	//if (start != NULL && goal != NULL) {
	//	vector<Position> passedPos;
	//	cout << "Task1: " << start->FindGoal(goal, 0, gridX, gridY, &passedPos).size() - 1;
	//}


	// ASTAR::
	//------------------------------------------------------------------
	vector<AStarCoordinate> closed;
	vector<AStarCoordinate> open;

	start->f = 0;

	AStarCoordinate aStarStart(start->GetX(), start->GetY(), NULL, 'a', -1);
	aStarStart.g = 0;
	aStarStart.f = 0;
	aStarStart.h = 0;
	open.push_back(aStarStart);
	AStarCoordinate q = open.back();

	while (!open.empty()) {
		/*a) find the node with the least f on
		the open list, call it "q"*/
		q = open.back();
		int indexOfLeastF = open.size() - 1;
		for (int i = 0; i < open.size(); i++) {
			if (open[i].f < q.f) {
				q = open[i];
				indexOfLeastF = i;
			}
		}


		//b) pop q off the open list
		open.erase(open.begin() + indexOfLeastF);
		closed.push_back(q);

		/*c) generate q's 8 successors and set their 
		parents to q*/
		for (int i = q.x - 1; i <= q.x + 1; i += 2) {
			if (i < 0 || i >= gridX) {
				continue;
			}
			AStarGenerateSuccessor(i, q.y, goal, &open, &closed, &q, lines[i].at(q.y));
		}
		for (int i = q.y - 1; i <= q.y + 1; i += 2) {
			if (i < 0 || i >= gridY) {
				continue;
			}
			AStarGenerateSuccessor(q.x, i, goal, &open, &closed, &q, lines[q.x].at(i));
		}

		//push q on the closed list
		//closed.push_back(q);

		//for (int i = 0; i < open.size(); i++) {
		//	if (open[i].parent == &q) {
		//		open[i].parent = &closed[closed.size() - 1];
		//	}
		//}
	}
}