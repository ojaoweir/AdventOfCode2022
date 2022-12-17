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

	virtual bool IsOpen() {
		return false;
	}

	virtual void AddInt(int value) {

	}

	virtual void OpenChild() {

	}

	virtual void CloseChild() {

	}
};

class PacketInt : public PacketObject {

	int value;
public:
	PacketInt(int value) {
		this->value = value;
	}

	void Print() {
		cout << value;
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
	bool isOpen = true;
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
		cout << '[';
		for (int i = 0; i < objectsInList.size(); i++) {
			objectsInList[i].Print();
			cout << ',';
		}
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

	void AddInt(int value) {
		if (objectsInList.back().IsOpen()) {
			objectsInList.back().AddInt(value);
		}
		else {
			PacketInt pi(value);
			objectsInList.push_back(pi);
		}
	}
	
	bool IsOpen() {
		return isOpen;
	}

	bool HasOpenChild() {
		return objectsInList.back().IsOpen();
	}

	void OpenChild() {
		if (HasOpenChild()) {
			objectsInList.back().OpenChild();
		}
		else {
			PacketList pl;
			objectsInList.push_back(pl);
		}
	}

	void CloseChild() {
		if (HasOpenChild()) {
			objectsInList.back().CloseChild();
		}
		else {
			isOpen = false;
		}
	}
};

void Day13_2::Run() {
	PacketObject* po;
	PacketList pl;
	po = &pl;

	po->Print();
}
