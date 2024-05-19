#ifndef MEM

#define MEM
#pragma once

#include <vector>
using namespace std;
class Memory
{
public:
	vector<int> mem;
	Memory() {
		mem.clear();
		mem.reserve(128000);
	}
	void insert(int address, int val) {
		if(address < 128000)
		mem.at(address) = val;
	}

	int get(int address) {
		if (address < 128000) return mem.at(address);
	}
};


#endif // !MEM
