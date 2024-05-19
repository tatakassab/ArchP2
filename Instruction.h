#ifndef INST
#define INST
#include"Memory.h"

enum STATE
{
	INITIAL,
	ISSUED,
	EXECUTINGOFFSET,
	EXECUTING,
	EXECUTED,
	WRITTEN
};

#pragma once
class Instruction
{
public:
	int type;
	int execution_cycles_left;
	int offset_cycles_left;
	int source1, source2, result;
	int source1Index, source2Index, targetIndex;
	STATE state;
	int offset;
	bool branchWait;
	Instruction* branch;
	int issueTime, execStartTime, execEndTime, writeTime;
	Memory mem;
	int PC;
	Instruction(int Type, int execDuration, int s1, int s2, int rd, int Offset = 0, int offset_cycles = 0) {
		type = Type;
		execution_cycles_left = execDuration;
		offset_cycles_left = offset_cycles;
		state = STATE::INITIAL;
		branchWait = false;
		offset = Offset;
		source1Index = s1;
		source2Index = s2;
		targetIndex = rd;
		branch = nullptr;
		PC = 0;
	}
	void CalculateAddress() {
		if (type == 0) { //LOAD
			offset = source1 + offset;
		}
		else if (type == 1) { //STORE
			offset = source1 + offset;
		}
	}
	void Execute() {
		if (type == 0) { //LOAD
			result = mem.get(offset);
		}
		else if (type == 1) { //STORE
			result = source1;
		}
		else if (type == 2) { //BRANCH
			if (source1 == source2) {
				result = 1;
			}
			else result = 0;
			offset = offset + PC + 1;
		}
		else if (type == 3) {
			result = PC+1;
		}
		else if (type == 4) {
			result = 1;
		}
		else if (type == 5) { //ADD
			result = source1 + source2;
		}
		else if (type == 6) { //ADDI
			result = source1 + offset;
		}
		else if (type == 7) { //NAND
			result = ~(source1 & source2);
		}
		else if (type == 8) { //MUL
			result = source1 * source2;
		}
	}
};

#endif // !INST

