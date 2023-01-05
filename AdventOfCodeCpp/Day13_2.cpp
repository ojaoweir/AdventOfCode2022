#include <iostream>
#include <vector>

#include "Day13_2.h"
#include "PacketObject2.h"
#include "PacketList2.h"
#include "PacketInt2.h"

using namespace std;

void Day13_2::Run() {
	PacketObject2* po;
	PacketList2 pl;
	po = &pl;

	po->Print();
}
