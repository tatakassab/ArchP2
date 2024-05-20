#ifndef SIM
#define SIM

#include <vector>
#include "ReservationStation.h"
#include "Instruction.h"
#include "Memory.h"
#include "Register.h"
#include <iostream>
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
	int totalbranches = 0;
	int totalpredictionfail = 0;
	Instruction* LastBranch;
	int issues;
	Simulator(vector<Instruction> insts, vector<ReservationStation> reserves, int Issues = 1) {
		issues = Issues;
		instructions = insts;
		stations = reserves;
		registers = vector<Register> (8);
		for (int i = 0; i < 8; i++) {
			registers.at(i).data = 0;
		}
		for (int i = 0; i < instructions.size(); i++) instructions.at(i).mem = mem;
		PC = 0;
		time = 0;
		while(PC < instructions.size() || !allDone())
			Simulate();
		printdata();
	}
	~Simulator() {
		for (int i = 0; i < finished.size(); i++) {
			delete finished.at(i);
		}
	}
	void Simulate();
	int WriteBack();
	void Execute();
	void Issue();
	bool allDone() {
		for (int i = 0; i < stations.size(); i++) {
			if (stations.at(i).busy) return false;
		}
		return true;
	}
	void printdata() {
		cout << "Total Execution Time = " << time << " Cycles" << endl;
		cout << "IPC = " << finished.size() / (1.0f* time) << " Instructions per cycles" << endl;
		cout << "Branch Misprediction Ratio = " << totalpredictionfail / (1.0f * totalbranches) << endl;
		cout << "Instruction Data:\n";
		for (int i = 0; i < finished.size(); i++) {
			cout << "Instruction: " << finished.at(i)->inst << "\tIssuing Time = " << finished.at(i)->issueTime << "\tExecution Start Time = " << finished.at(i)->execStartTime << "\tExecution End Time = " << finished.at(i)->execEndTime << "\tWrite Time = " << finished.at(i)->writeTime << endl;
		}
	}
};


#endif // !SIM