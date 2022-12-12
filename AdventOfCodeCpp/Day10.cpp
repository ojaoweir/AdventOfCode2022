#include "Day10.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "FileReader.h"
#include "StringUtils.h"

using namespace std;

void UpdateCycle(int* cycle, int* x, int* TotalSignalStrength, int signalCycleIntervalls, int firstCycleTick, vector<string>* crtOutput) {
	char addToCrt = '.';
	if (abs(*x - (*cycle % 40)) < 2) {
		addToCrt = '#';
	}
	crtOutput->back().push_back(addToCrt);
	*cycle = *cycle + 1;
	if ((*cycle + firstCycleTick) % signalCycleIntervalls == 0) {
		*TotalSignalStrength += *x * *cycle;
	}
	int cycles = *cycle;
	int row = crtOutput->size();
	if ((cycles - row * 40) == 0) {
		crtOutput->push_back("");
	}
}

void Day10::Run() {
	vector<string> lines = FileReader::ReadFile("ass10.txt");
	lines.pop_back();
	int cycle = 0;
	int x = 1;
	int totalSignalStrength = 0;
	vector<string> crtOutput;
	crtOutput.push_back("");

	for (int i = 0; i < lines.size(); i++) {
		vector<string> commands = StringUtils::split(lines[i], ' ');
		if (commands.front() == "noop") {
			UpdateCycle(&cycle, &x, &totalSignalStrength, 40, 20, &crtOutput);
		}
		else {
			for (int j = 0; j < 2; j++) {
				UpdateCycle(&cycle, &x, &totalSignalStrength, 40, 20, &crtOutput);
			}
			x += stoi(commands.back());
		}
	}

	cout << "Task1: " << totalSignalStrength << endl;
	cout << "Task2:" << endl;

	for (int i = 0; i < crtOutput.size(); i++) {
		cout << crtOutput[i] << endl;
	}
}