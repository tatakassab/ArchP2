#include <iostream>
#include "Simulator.h"

int main()
{
    vector<Instruction> Is;

    ////TEST 2
    Is.push_back(Instruction("Load R3, 10(R0)", 0, 0, 0, 3, 10));
    Is.push_back(Instruction("Load R2, 20(R0)", 0, 0, 0, 2, 20));
    Is.push_back(Instruction("Call label 2 (to ADD R3 R3 R2)", 3, 0, 0, 1, 3));
    Is.push_back(Instruction("ADD R3 R3 R2", 5, 3, 2, 3));
    Is.push_back(Instruction("ADDI R2 R2 -1", 6, 2, 0, 2, -1));
    Is.push_back(Instruction("BEQ R2, R0, 2", 2, 0, 2, 0, 1));
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
