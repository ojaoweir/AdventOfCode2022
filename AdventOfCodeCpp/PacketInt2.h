
#pragma once
#include "PacketList2.h"
#include "PacketObject2.h"

using namespace std;

class PacketInt2 : public PacketObject2
{
private:
	int value;
public:
	PacketInt2(int value);

	void Print();

	PacketList2 ToList();

	int CompareTo(PacketObject2 other);
};

