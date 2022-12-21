#pragma once
#include "PacketObject2.h"
#include "PacketList2.h"
#include "PacketInt2.h"

#include <vector>
#include <iostream>

using namespace std;

class PacketList2 : public PacketObject2
{
	vector<PacketObject2> objectsInList;
	bool isOpen = true;
public:

	PacketList2() {

	}
	PacketList2(PacketInt2 pi) {
		objectsInList.push_back(pi);
	}

	PacketList2 ToList() {
		return *this;
	}

	void Print() {
		cout << '[';
		for (int i = 0; i < objectsInList.size(); i++) {
			objectsInList[i].Print();
			cout << ',';
		}
	}

	int CompareTo(PacketObject2 other) {
		PacketList2 otherList = other.ToList();
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
			PacketInt2 pi(value);
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
			PacketList2 pl;
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

