#ifndef RESERVE
#define RESERVE
#include "Instruction.h"

#pragma once
class ReservationStation
{
public:
	vector<int> type;
	bool busy;
	Instruction* currentInst;
	ReservationStation* src1;
	ReservationStation* src2;
	int speed;
	int offspeed;

	ReservationStation(vector<int> Type, int s, int os = 0) {
		type = Type;
		busy = false;
		src1 = nullptr;
		src2 = nullptr;
		currentInst = nullptr;
		speed = s;
		offspeed = os;
	}
	void Issue(Instruction* inst, int time) {
		busy = true;
		currentInst = inst;
		currentInst->issueTime = time;
		currentInst->state = STATE::ISSUED;
		currentInst->execution_cycles_left = speed;
		currentInst->offset_cycles_left = offspeed;
	}
	void execute(vector<Instruction*> &LoadStore, int time) {
		if (src1 == nullptr && src2 == nullptr && currentInst->state == STATE::ISSUED && currentInst->branchWait == false) {
			if (currentInst->type != 1 && currentInst->type != 0) {
				currentInst->state = STATE::EXECUTING;
				currentInst->execStartTime = time;
				currentInst->execution_cycles_left--;
			}
			else {
				currentInst->state = STATE::EXECUTINGOFFSET;
				currentInst->execStartTime = time;
				currentInst->offset_cycles_left--;
			}
		}
		else if (currentInst->state == STATE::EXECUTING) {
			currentInst->execution_cycles_left--;
		}
		else if (currentInst->state == STATE::EXECUTINGOFFSET) {
			if(currentInst->offset_cycles_left > 0)
				currentInst->offset_cycles_left--;
			else {
				if (currentInst->offset_cycles_left == 0) {
					currentInst->CalculateAddress();
					currentInst->offset_cycles_left--;
				}
				bool flag = false;
				for (int i = 0; i < LoadStore.size(); i++) {
					if (LoadStore.at(i) == currentInst) {
						break;
					}
					if (LoadStore.at(i)->type == 1) {
						if (LoadStore.at(i)->offset_cycles_left > 0 || (LoadStore.at(i)->offset_cycles_left == 0 && LoadStore.at(i)->offset == currentInst->offset)) {
							flag = true;
							break;
						}
					}
					else if (LoadStore.at(i)->type == 0) {
						if (currentInst->type == 1 && (LoadStore.at(i)->offset_cycles_left > 0 || (LoadStore.at(i)->offset_cycles_left == 0 && LoadStore.at(i)->offset == currentInst->offset))) {
							flag = true;
							break;
						}
					}
				}
				if (!flag) {
					currentInst->state = STATE::EXECUTING;
					currentInst->execution_cycles_left--;
				}
			}
		}

		if (currentInst->state == STATE::EXECUTING && currentInst->execution_cycles_left == 0) {
			currentInst->Execute();
			currentInst->state = STATE::EXECUTED;
			currentInst->execEndTime = time;
		}
	}

	bool satisfys(int t) {
		for (int i = 0; i < type.size(); i++) {
			if (t == type.at(i)) {
				return true;
			}
		}
		return false;
	}
};

#endif // !RESERVE

