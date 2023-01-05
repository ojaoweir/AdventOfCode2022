#include "PacketList2.h"
#include "PacketObject2.h"
#include "PacketInt2.h"


vector<PacketObject2> objectsInList;
bool isOpen = true;

PacketList2::PacketList2() {

}
PacketList2::PacketList2(PacketInt2 pi) {
	objectsInList.push_back(pi);
}

PacketList2 PacketList2::ToList() {
		return *this;
	}

void PacketList2::Print() {
	cout << '[';
	for (int i = 0; i < objectsInList.size(); i++) {
		objectsInList[i].Print();
		cout << ',';
	}
}

int PacketList2::CompareTo(PacketObject2 other) {
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

void PacketList2::AddInt(int value) {
	if (objectsInList.back().IsOpen()) {
		objectsInList.back().AddInt(value);
	}
	else {
		PacketInt2 pi(value);
		objectsInList.push_back(pi);
	}
}

bool PacketList2::IsOpen() {
	return isOpen;
}

bool PacketList2::HasOpenChild() {
	return objectsInList.back().IsOpen();
}

void PacketList2::OpenChild() {
	if (HasOpenChild()) {
		objectsInList.back().OpenChild();
	}
	else {
		PacketList2 pl;
		objectsInList.push_back(pl);
	}
}

void PacketList2::CloseChild() {
	if (HasOpenChild()) {
		objectsInList.back().CloseChild();
	}
	else {
		isOpen = false;
	}
}
