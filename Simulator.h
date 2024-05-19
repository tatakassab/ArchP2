#ifndef SIM
#define SIM

#include <vector>
#include "ReservationStation.h"
#include "Instruction.h"
#include "Memory.h"
#include "Register.h"
using namespace std;

#pragma once
class Simulator
{
public:
	vector <Instruction> instructions;
	vector <ReservationStation> stations;
	vector <Register> registers;
	vector <Instruction*> loadStore;
	vector <Instruction*> finished;
	Memory mem;

	int time = 0;
	int PC = 0;
	int branchesInFlight = 0;
	Instruction* LastBranch;
	Simulator(vector<Instruction> insts, vector<ReservationStation> reserves) {
		instructions = insts;
		stations = reserves;
		registers.reserve(8);
		for (int i = 0; i < 8; i++) {
			registers.at(i).data = 0;
		}
		for (int i = 0; i < instructions.size(); i++) instructions.at(i).mem = mem;
		PC = 0;
		time = 0;
		while(PC != instructions.size() && !allDone())
			Simulate;
		printdata();
	}
	~Simulator() {
		for (int i = 0; i < finished.size(); i++) {
			delete finished.at(i);
		}
	}
	void Simulate();
	void WriteBack();
	void Execute();
	void Issue();
	bool allDone() {
		for (int i = 0; i < stations.size(); i++) {
			if (stations.at(i).busy) return false;
		}
		return true;
	}
	void printdata();
};


#endif // !SIM