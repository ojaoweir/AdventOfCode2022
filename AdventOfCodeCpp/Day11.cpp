#include <vector>
#include <string>
#include <queue>

#include "Day11.h"
#include "FileReader.h"
#include "StringUtils.h"

class Monkey {
	queue<int> items;
	int executeCounts = 0;

public:
	char operationType;
	int operationValue;
	int testDivisionFactor;
	int trueMonkey;
	int falseMonkey;

	void AddItem(int item) {
		items.push(item);
	}

	int GetScore() {
		return executeCounts;
	}

	void Execute(vector<Monkey>* monkeys, int index) {
		//cout << "Monkey " << index << ":" << endl;
		while (!items.empty()) {
			executeCounts++;
			string indent = "   ";

			int item = items.front();
			//cout << indent << "Monkey inspects an item with a worry level of " << item << "." << endl;
			items.pop();
			switch (operationType) {
			case '+':
				item += operationValue;
				break;
			case '*':
				item *= operationValue;
				break;
			case '^':
				item *= item;
				break;
			default:
				break;
			}
			//cout << indent << indent << "Worry level is modified by " << operationValue << " to " << item << "." << endl;

			item = item / 3;
			//cout << indent << indent << "Monkey gets bored with item.Worry level is divided by 3 to " << item << "." << endl;

			int toMonkey;
			if (item % testDivisionFactor == 0) {
				toMonkey = trueMonkey;
			}
			else {
				toMonkey = falseMonkey;
			}
			//cout << indent << indent << "Item with worry level "<< item <<" is thrown to monkey " << toMonkey << "." << endl;

			monkeys->at(toMonkey).AddItem(item);
		}

	}
	
	void ExecuteTask2(vector<Monkey>* monkeys, int index, int modulo) {
		//cout << "Monkey " << index << ":" << endl;
		while (!items.empty()) {
			executeCounts++;
			string indent = "   ";

			int item = items.front();
			//cout << indent << "Monkey inspects an item with a worry level of " << item << "." << endl;
			items.pop();

			item = item % modulo;
			//cout << indent << indent << "Worry level is modified by " << operationValue << " to " << item << "." << endl;

			item = item / 3;
			//cout << indent << indent << "Monkey gets bored with item.Worry level is divided by 3 to " << item << "." << endl;

			int toMonkey;
			if (item % testDivisionFactor == 0) {
				toMonkey = trueMonkey;
			}
			else {
				toMonkey = falseMonkey;
			}
			//cout << indent << indent << "Item with worry level "<< item <<" is thrown to monkey " << toMonkey << "." << endl;

			monkeys->at(toMonkey).AddItem(item);
		}

	}

	void Print(int index) {
		cout << "Monkey " << index << ": ";
		for (int i = 0; i < items.size(); i++) {
			int temp = items.front();
			items.pop();
			cout << temp << ", ";
			items.push(temp);
		}
		cout << endl;
	}
};

vector<Monkey> CreateMonkeys(vector<string>* lines) {
	vector<Monkey> monkeys;

	for (int monkeyLineIndex = 0; monkeyLineIndex < lines->size(); monkeyLineIndex += 7) {
		Monkey monkey;

		// Starting items
		vector<string> input = StringUtils::split(lines->at(monkeyLineIndex + 1), ':');
		input = StringUtils::split(input.back(), ',');
		for (int j = 0; j < input.size(); j++) {
			monkey.AddItem(stoi(input[j]));
		}

		//Operation
		input = StringUtils::split(lines->at(monkeyLineIndex + 2), ':');
		input = StringUtils::split(input.back(), ' ');
		if (input.back() == "old") {
			monkey.operationType = '^';
		}
		else {
			monkey.operationValue = stoi(input.back());
			input.pop_back();
			monkey.operationType = input.back().at(0);
		}

		//Test
		input = StringUtils::split(lines->at(monkeyLineIndex + 3), ' ');
		monkey.testDivisionFactor = stoi(input.back());

		//TRUE
		input = StringUtils::split(lines->at(monkeyLineIndex + 4), ' ');
		monkey.trueMonkey = stoi(input.back());

		//FALSE
		input = StringUtils::split(lines->at(monkeyLineIndex + 5), ' ');
		monkey.falseMonkey = stoi(input.back());

		monkeys.push_back(monkey);
	}
	return monkeys;
}

void printScores(vector<Monkey>* monkeys, int task) {
	int maxMonkey = 0;
	int secondMaxMonkey = 0;
	for (int j = 0; j < monkeys->size(); j++) {
		int monkeyScore = monkeys->at(j).GetScore();
		if (monkeyScore > maxMonkey) {
			secondMaxMonkey = maxMonkey;
			maxMonkey = monkeyScore;
		}
		else if (monkeyScore > secondMaxMonkey) {
			secondMaxMonkey = monkeyScore;
		}
	}
	cout << endl << "Task " << task << ": " << secondMaxMonkey * maxMonkey;
}

void Task1(vector<Monkey> monkeys) {
	cout << endl << "Round " << 0 << ":" << endl;
	for (int j = 0; j < monkeys.size(); j++) {
		monkeys[j].Print(j);
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < monkeys.size(); j++) {
			monkeys[j].Execute(&monkeys, j);
		}
		cout << endl << "Round " << i + 1 << ":" << endl;
		for (int j = 0; j < monkeys.size(); j++) {
			monkeys[j].Print(j);
		}
	}

	printScores(&monkeys,1);
}

void Task2(vector<Monkey> monkeys) {

	int commmonDenominator = 1;
	for (int i = 0; i < monkeys.size(); i++) {
		commmonDenominator *= monkeys[i].testDivisionFactor;
	}


	for (int i = 1; i <= 10000; i++) {
		for (int j = 0; j < monkeys.size(); j++) {
			monkeys[j].ExecuteTask2(&monkeys, j, commmonDenominator);
		}
		if (i == 1 || i == 20 || i % 1000 == 0) {
			cout << endl << "== After round " << i << "==" << endl;
			for (int j = 0; j < monkeys.size(); j++) {
				cout << "Monkey " << j << " inspected items " << monkeys[j].GetScore() << " times." << endl;
			}
		}
	}

	printScores(&monkeys,2);

}

void Day11::Run() {
	vector<string> lines = FileReader::ReadFile("ass11.txt");
	lines.pop_back();
	
	vector<Monkey> monkeys = CreateMonkeys(&lines);
	Task1(monkeys);
	cout << endl << "--------------------------------------------------" << endl;
	Task2(monkeys);

	

	//cout << endl << "Task2: " << secondMaxMonkey << " : " << maxMonkey;
}
