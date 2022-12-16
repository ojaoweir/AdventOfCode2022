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
	int Id = 0;

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
			if (children[children.size() - 1].HasChildOpen()) {
				children[children.size() - 1].CloseChild();
			}
			else {
				currentChild++;
			}
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

	int size() {
		return values.size() + children.size();
	}

	int ChildType(int childIndex) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i].Id == childIndex) {
				return 0;
			}
		}
		for (int i = 0; i < values.size(); i++) {
			if (values[i].Id == childIndex) {
				return 1;
			}
		}
	}

	void CompareChild(int compareChild, Packet other) {
		int childType = ChildType(compareChild);
		switch (childType)
		{
		case 0:
			children[GetChildId(compareChild)].CompareChild(compareChild, other.GetChild(other.GetChildId(compareChild)));
		default:
			break;
		}
	}

	Packet GetChild(int childIndex) {
		return children[childIndex];
	}

	int GetChildId(int childId) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i].Id == childId) {
				return i;
			}
		}
		return -1;
	}

	int GetValueId(int childId) {
		for (int i = 0; i < values.size(); i++) {
			if (values[i].Id == childId) {
				return i;
			}
		}
		return -1;
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
			packet.CloseChild();
			break;
		case ',':
			intEnd = i;
			AddToPacket(&packet, input, &intStart, &intEnd, i+1);
			break;
		default:
			break;
		}
	}

	return packet;
	}

class PacketPair {
public:
	Packet left;
	Packet right;

	void Print() {
		left.print();
		cout << endl;
		right.print();
		cout << endl << endl;
	}

	bool IsInOrder() {
		for (int compareIndex = 0; 
			compareIndex < max(left.size(), right.size()); 
			compareIndex++) {
			if (left.ChildType(compareIndex) == right.ChildType(compareIndex)) {
				left.CompareChild(compareIndex, right);
			}
		}
		return false;
	}
};

void Day13::Run() {
	vector<string> lines = FileReader::ReadFile("ass13.txt");
	lines.pop_back();

	vector<PacketPair> packetPairs;
	int totalOutOfOrder = 0;

	Packet p = CreateNew(lines[0]);
	for (int i = 0; i < lines.size(); i += 3) {
		PacketPair pp;
		pp.left = CreateNew(lines[i]);
		pp.right = CreateNew(lines[i + 1]);
		
		pp.Print();

		if (!pp.IsInOrder()) {
			totalOutOfOrder += i + 1;
		}
	}
}