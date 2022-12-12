#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FileReader.h"
#include "Coordinate.h"
#include "StringUtils.h"

using namespace std;

class Command {
	char direction;
	int steps;

public:
	Command(string commandLine) {
		vector<string> commands = StringUtils::split(commandLine, ' ');
		direction = commands.front()[0];
		steps = stoi(commands.back());
	}

	void Execute(coordinateList* coordinateList, coordinate* tail, coordinate* head) {
		for (int i = 0; i < steps; i++) {
			head->MoveDirection(direction);
			if (!tail->AdjecentTo(*head)) {
				tail->MoveTowards(head);
				coordinateList->Add(*tail);
			}
		}
	}

	void ExecuteOnList(coordinateList* rope, coordinateList* tailPositions) {
		for (int i = 0; i < steps; i++) {
			bool tailMoved = rope->MoveRope(direction);
			if (tailMoved) {
				tailPositions->Add(rope->GetTailPosition());
			}
		}
	}
};


class Day9
{

public:

	static void Run() {
		vector<string> lines = FileReader::ReadFile("ass9.txt");
		lines.pop_back();

		coordinate tail(0, 0);
		coordinate head(0, 0);
		coordinateList tailCoordinates;
		tailCoordinates.Add(tail);


		coordinateList rope = coordinateList::createRope(10);
		coordinateList tailCoordinatesOnRope;

		tailCoordinatesOnRope.Add(rope.GetTailPosition());

		for (int i = 0; i < lines.size(); i++) {
			Command c(lines[i]);
			c.Execute(&tailCoordinates, &tail, &head);
			c.ExecuteOnList(&rope, &tailCoordinatesOnRope);
		}

		cout << "Task1 Total: " << tailCoordinates.Size() << endl;
		cout << "Task2 Total: " << tailCoordinatesOnRope.Size() << endl;
	}
};

