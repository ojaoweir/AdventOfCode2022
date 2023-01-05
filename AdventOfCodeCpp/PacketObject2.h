
#pragma once
#include <iostream>

#include "PacketList2.h";

using namespace std;

class PacketObject2
{
public:
	virtual void Print();

	virtual int CompareTo(PacketObject2 other);

	virtual PacketList2 ToList();

	virtual bool IsOpen();

	virtual void AddInt(int value);

	virtual void OpenChild();

	virtual void CloseChild();

};
