#include <iostream>
#include <vector>

#include "Day13_2.h"

using namespace std;

class PacketObject {
public:
	virtual void Print() {
		cout << "I am a packetObject";
	}

	virtual int CompareTo(PacketObject other) {
		return -1;
	}

	virtual PacketList ToList() {
		PacketList pl;
		return pl;
	}
};

class PacketInt : public PacketObject {

	int value;
public:
	void Print() {
		cout << "I am an int";
	}

	PacketList ToList() {
		PacketList pl(*this);
		return pl;
	}

	int CompareTo(PacketObject other) {
		PacketInt* otherPtr = dynamic_cast<PacketInt*>(&other);
		if (otherPtr == nullptr) {
			return ToList().CompareTo(other);
		}
		if (otherPtr->value == value) {
			return 0;
		}
		if (value < otherPtr->value) {
			return 1;
		}
		if (value > otherPtr->value) {
			return -1;
		}
	}
};

class PacketList : public PacketObject {
	vector<PacketObject> objectsInList;
public:

	PacketList() {

	}
	PacketList(PacketInt pi) {
		objectsInList.push_back(pi);
	}

	PacketList ToList() {
		return *this;
	}

	void Print() {
		cout << "I have " << objectsInList.size() << " children";
	}

	int CompareTo(PacketObject other) {
		PacketList otherList = other.ToList();
		for (int i = 0;
			i < min(objectsInList.size(), otherList.objectsInList.size());
			i++) {
			int comparison = objectsInList[i].CompareTo(otherList.objectsInList[i]);
			if (comparison != 0) {
				return comparison;
			}
		}
		return 0;
	}

};

void Day13_2::Run() {
	PacketObject* po;
	PacketList pl;
	po = &pl;

	po->Print();
}
