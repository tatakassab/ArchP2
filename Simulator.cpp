#include "Simulator.h"

void Simulator::Simulate()
{
	int x = WriteBack();
	Execute();
	for(int i = 0; i < issues; i++)
		Issue();
	if (x != -1)
		stations.at(x).busy = false;
	time++;
}

int Simulator::WriteBack()
{
	for (int i = 0; i < stations.size(); i++) {
		if (stations.at(i).busy && stations.at(i).currentInst->state == STATE::EXECUTED) {
			if (stations.at(i).currentInst->type != 1 && stations.at(i).currentInst->type != 2 && stations.at(i).currentInst->type != 4) {
				for (int j = 0; j < registers.size(); j++) {
					if (registers.at(j).Qi == &stations.at(i) && j != 0) {
						registers.at(j).Qi = nullptr;
						registers.at(j).data = stations.at(i).currentInst->result;
					}
				}
				for (int j = 0; j < stations.size(); j++) {
					if (stations.at(j).src1 == &stations.at(i)) {
						stations.at(j).src1 = nullptr;
						stations.at(j).currentInst->source1 = stations.at(i).currentInst->result;
					}
					if (stations.at(j).src2 == &stations.at(i)) {
						stations.at(j).src2 = nullptr;
						stations.at(j).currentInst->source2 = stations.at(i).currentInst->result;
					}
				}
			}
			if(stations.at(i).currentInst->type == 1) {
				mem.insert(stations.at(i).currentInst->offset, stations.at(i).currentInst->result);
			}
			if (stations.at(i).currentInst->type == 2 || stations.at(i).currentInst->type == 3 || stations.at(i).currentInst->type == 4) {
				if (stations.at(i).currentInst->result == 1 || stations.at(i).currentInst->type == 3) {
					totalpredictionfail++;
					if (stations.at(i).currentInst->type == 4) {
						PC = registers.at(1).data;
					}
					else {
						PC = stations.at(i).currentInst->offset;
					}
					for (int j = 0; j < stations.size(); j++) {
						if (stations.at(j).busy && stations.at(j).currentInst->branchWait) {
							delete stations.at(j).currentInst;
							stations.at(j).busy = false;
							stations.at(j).currentInst = nullptr;
						}
					}
				}
				totalbranches++;
				branchesInFlight = 0;
				for (int j = 0; j < stations.size(); j++) {
					if (stations.at(j).busy && stations.at(j).currentInst->branch == stations.at(i).currentInst) {
						stations.at(j).currentInst->branch = nullptr;
						stations.at(j).currentInst->branchWait = false;
					}
				}
			}
			loadStore.erase(remove(loadStore.begin(), loadStore.end(), stations.at(i).currentInst), loadStore.end());
			stations.at(i).currentInst->writeTime = time;
			finished.push_back(stations.at(i).currentInst);
			return i;
		}
	}
	return -1;
}

void Simulator::Execute()
{
	for (int i = 0; i < stations.size(); i++) {
		if(stations.at(i).busy)
			stations.at(i).execute(loadStore,time);
	}
}

void Simulator::Issue()
{
	if (PC != instructions.size()) {
		for (int i = 0; i < stations.size(); i++) {
			if (!stations.at(i).busy && stations.at(i).satisfys(instructions.at(PC).type)) {
				Instruction* inst = new Instruction(instructions.at(PC));
				inst->PC = PC;
				stations.at(i).Issue(inst, time);
				if (branchesInFlight > 0) {
					inst->branchWait = true;
					inst->branch = LastBranch;
				}
				if (inst->type == 2) {
					branchesInFlight++;
					LastBranch = inst;
				}

				if (registers.at(inst->source1Index).Qi != nullptr) {
					stations.at(i).src1 = registers.at(inst->source1Index).Qi;
				}
				else {
					inst->source1 = registers.at(inst->source1Index).data;
					stations.at(i).src1 = nullptr;
				}
				if (inst->type != 0) {
					if (registers.at(inst->source2Index).Qi != nullptr) {
						stations.at(i).src2 = registers.at(inst->source2Index).Qi;
					}
					else {
						inst->source2 = registers.at(inst->source2Index).data;
						stations.at(i).src2 = nullptr;
					}
					if (inst->type != 1 && inst->targetIndex != 0) {
						registers.at(inst->targetIndex).Qi = &stations.at(i);
					}
				}
				if (inst->type == 0 || inst->type == 1) {
					loadStore.push_back(inst);
				}
				PC++;
				return;
			}
		}
	}
}
