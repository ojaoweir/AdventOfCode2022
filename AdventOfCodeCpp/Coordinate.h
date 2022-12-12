#pragma once

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class coordinate {
	int x;
	int y;

public:
	coordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void Print() {
		cout << "X: " << x << " Y: " << y << endl;
	}

	void MoveTowards(coordinate* target) {
		int moveX = 0;
		int moveY = 0;
		int xDiff = target->x - x;
		moveX = (xDiff > 0) - (xDiff < 0);
		int yDiff = target->y - y;
		moveY = (yDiff > 0) - (yDiff < 0);

		x += moveX;
		y += moveY;
	}

	bool Equal(coordinate other) {
		return x == other.x && y == other.y;
	}

	bool AdjecentTo(coordinate other) {
		return abs(x - other.x) < 2 && abs(y - other.y) < 2;
	}

	void MoveDirection(char direction) {
		switch (direction)
		{
		case 'R':
			x++;
			break;
		case 'U':
			y++;
			break;
		case 'L':
			x--;
			break;
		case 'D':
			y--;
			break;
		default:
			break;
		}
	}
};

class coordinateList {
	vector<coordinate> coordinates;

public:

	static coordinateList createRope(int length) {
		coordinateList c;
		for (int i = 0; i < length; i++) {
			c.coordinates.push_back(coordinate(0, 0));
		}
		return c;
	}

	void Add(int x, int y) {
		coordinate c(x, y);
		Add(c);
	}

	void Add(coordinate c) {
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

	void Print() {
		for (int i = 0; i < coordinates.size(); i++) {
			coordinates[i].Print();
		}
	}

	bool MoveRope(char direction) {
		coordinate* head = &coordinates.front();
		head->MoveDirection(direction);
		for (int i = 1; i < coordinates.size(); i++) {
			if (!coordinates[i].AdjecentTo(coordinates[i - 1])) {
				coordinates[i].MoveTowards(&coordinates[i - 1]);
			}
			else {
				return false;
			}
		}
		return true;
	}

	coordinate GetTailPosition() {
		return coordinates.back();
	}
};
