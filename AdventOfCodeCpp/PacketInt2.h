#pragma once
#include "PacketObject2.h"

using namespace std;

class PacketInt2 : public PacketObject2
{

	int value;
public:
	PacketInt2(int value) {
		this->value = value;
	}

	void Print() {
		cout << value;
	}

	PacketList ToList() {
		PacketList pl(*this);
		return pl;
	}

	int CompareTo(PacketObject2 other) {
		PacketInt2* otherPtr = dynamic_cast<PacketInt2*>(&other);
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

