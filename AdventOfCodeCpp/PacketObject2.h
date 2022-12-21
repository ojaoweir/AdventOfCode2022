#pragma once
#include <iostream>

#include "PacketList2.h";

using namespace std;

class PacketObject2
{
public:
	virtual void Print() {
		cout << "I am a packetObject";
	}

	virtual int CompareTo(PacketObject2 other) {
		return -1;
	}

	virtual PacketList2 ToList() {
		PacketList2 pl;
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

