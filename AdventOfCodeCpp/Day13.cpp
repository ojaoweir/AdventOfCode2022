#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


#include "Day13.h"
#include "StringUtils.h"
#include "FileReader.h"

using namespace std;

class ListMarker {
public:
	int start = -1;
	int end = -1;
};

class PacketInt {
	int value;

public:
	PacketInt(int value) {
		this->value = value;
	}

	void Print() {
		cout << value << ',';
	}
	int Id;
};


class Packet {
	int currentChild = -1;
	vector<Packet> children;
	vector<PacketInt> values;
public:
	int Id;

	void AddChild() {
		if (HasChildOpen()) {
			children[children.size()-1].AddChild();
		}
		else {
			currentChild++;
			Packet child;
			child.Id = currentChild;
			children.push_back(child);
		}
	}

	void CloseChild() {
		if (HasChildOpen()) {
			children[children.size() - 1].CloseChild();
		}
		else {
			currentChild++;
		}
	}

	void AddInt(int value) {
		if (HasChildOpen()) {
			children[children.size() - 1].AddInt(value);
		}
		else {
			currentChild++;
			PacketInt packetInt(value);
			packetInt.Id = currentChild;
			values.push_back(packetInt);
		}
	}

	int HasChildOpen() {
		if (children.empty()) {
			return false;
		}
		return children.back().Id == currentChild;
	}

	void print() {
		cout << "[";
		for (int i = 0; i <= currentChild; i++) {
			for (int j = 0; j < children.size(); j++) {
				if (children[j].Id == i) {
					children[j].print();
					break;
				}
			}
			for (int j = 0; j < values.size(); j++) {
				if (values[j].Id == i) {
					values[j].Print();
					break;
				}
			}
		}
		cout << ']';
	}
};

void AddToPacket(Packet* packet, string line, int* start, int* end, int newStart) {
	if (*start < *end) {
		packet->AddInt(stoi(line.substr(*start, *end - *start)));
	}
	*end = newStart;
	*start = *end;
}

Packet CreateNew(string input) {
	Packet packet;

	int intStart = 1;
	int intEnd = input.size() - 1;
	for (int i = 1; i < input.size(); i++) {
		char c = input[i];
		switch (c)
		{
		case '[':
			intEnd = i;
			packet.AddChild();
			AddToPacket(&packet, input, &intStart, &intEnd, i+1);
			break;
		case ']':
			intEnd = i;
			AddToPacket(&packet, input, &intStart, &intEnd, i+1);
			break;
		case ',':
			intEnd = i;
			packet.CloseChild();
			AddToPacket(&packet, input, &intStart, &intEnd, i+1);
			break;
		default:
			break;
		}
	}

	return packet;


	//vector<ListMarker> markers;

	//for (int i = 0; i < input.size(); i++) {
	//	if (input[i] == '[') {
	//		ListMarker newMarker;
	//		newMarker.start = i;
	//	}
	//	else if (input[i] == ']') {
	//		for (int i = markers.size() - 1; i >= 0; i++) {
	//			if (markers[i].end == -1) {
	//				markers[i].end = i;
	//			}
	//		}
	//	}

	//	for (int i = 0; i < markers.size(); i++) {
	//		int subStrStart = markers[i].start;
	//		int nextMarker = max(i + 1, (int)markers.size() - 1);

	//		for (int j = subStrStart; i < markers[i].end; i++) {
	//			int subStrEnd = min(markers[i].end, markers[nextMarker].start);
	//			string nextInputString = input.substr(subStrStart, subStrEnd - subStrStart);
	//		}
	//	}
	//}

	//vector<string> packetObjects = StringUtils::split(input, ',');

	//for (int i = 0; i < packetObjects.size(); i++) {
	//	if (packetObjects[i].at(0) == '[') {
	//		PacketObjectList packetList;

	//	}
	}

void Day13::Run() {
	vector<string> lines = FileReader::ReadFile("ass13.txt");
	lines.pop_back();

	Packet p = CreateNew(lines[0]);
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i] == "") {
			cout << endl;
			continue;
		}
		p = CreateNew(lines[i]);
		p.print();
		cout << endl;
	}
}