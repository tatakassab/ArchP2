#include <iostream>
#include "Simulator.h"

int main()
{
    vector<Instruction> Is;
    //TEST 1
    Is.push_back(Instruction("Load R1, 10(R0)", 0, 0, 0, 1, 10));
    Is.push_back(Instruction("ADD R2 R1 R1", 5, 1, 1, 2));
    Is.push_back(Instruction("NAND R3 R2 R1", 7, 2, 1, 3));
    Is.push_back(Instruction("ADDI R4 R3 -5", 6, 3, 0, 4, -5));
    Is.push_back(Instruction("MUL R5 R4 R2", 8, 4, 2, 5));
    Is.push_back(Instruction("Store R5, 20(R0)", 1, 5, 0, 0, 20));
    Is.push_back(Instruction("Call label 1 (to Load)", 3, 0, 0, 1, 8));
    Is.push_back(Instruction("Store R5, 40(R0)", 1, 0, 0, 5, 40));
    Is.push_back(Instruction("Load R6, 40(R0)", 0, 0, 0, 6, 40));
    Is.push_back(Instruction("BEQ R6, R0, 2", 2, 0, 6, 0, 2));
    Is.push_back(Instruction("Store R6, 50(R0)", 1, 6, 0, 0, 50));
    Is.push_back(Instruction("RET", 4, 1, 0, 0, 0));

    vector<ReservationStation> Ss;
    Ss.push_back(ReservationStation({ 0 }, 4, 2));
    Ss.push_back(ReservationStation({ 0 }, 4, 2));
    Ss.push_back(ReservationStation({ 1 }, 4, 2));
    Ss.push_back(ReservationStation({ 2 }, 1));
    Ss.push_back(ReservationStation({3,4}, 1));
    Ss.push_back(ReservationStation({ 5,6 },2));
    Ss.push_back(ReservationStation({ 5,6 },2));
    Ss.push_back(ReservationStation({ 5,6 },2));
    Ss.push_back(ReservationStation({ 5,6 },2));
    Ss.push_back(ReservationStation({ 7 },1));
    Ss.push_back(ReservationStation({ 7 },1));
    Ss.push_back(ReservationStation({ 8 },8));

    Simulator(Is, Ss);
}
