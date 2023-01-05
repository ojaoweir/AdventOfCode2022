#include "PacketInt2.h"
#include "PacketList2.h"

int value;

PacketInt2::PacketInt2(int value) {
	this->value = value;
}

void PacketInt2::Print() {
	cout << value;
}

PacketList2 PacketInt2::ToList() {
	PacketList2 pl(*this);
	return pl;
}

int PacketInt2::CompareTo(PacketObject2 other) {
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