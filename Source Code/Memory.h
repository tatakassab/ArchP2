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
		mem = vector<int>(128000);
		mem[10] = 1;
		mem[20] = 2;
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
