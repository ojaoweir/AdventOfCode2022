
#pragma once
#include "PacketObject2.h"
#include "PacketInt2.h"

#include <vector>
#include <iostream>

using namespace std;

class PacketList2 : public PacketObject2
{
private:
	vector<PacketObject2> objectsInList;
	bool isOpen;
public:

	PacketList2();
	PacketList2(PacketInt2 pi);

	PacketList2 ToList();

	void Print();

	int CompareTo(PacketObject2 other);

	void AddInt(int value);

	bool IsOpen();

	bool HasOpenChild();

	void OpenChild();

	void CloseChild();
};

