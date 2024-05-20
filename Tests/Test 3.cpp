#include <iostream>
#include "Simulator.h"

int main()
{
    vector<Instruction> Is;

    //TEST 3
    Is.push_back(Instruction("ADDI R4 R0 20", 6, 0, 0, 4, 20));
    Is.push_back(Instruction("ADDI R3 R0 0", 6, 0, 0, 3, 0));
    Is.push_back(Instruction("Call label 3 (to ADDI R3 R3 5)", 3, 0, 0, 1, 3));
    Is.push_back(Instruction("ADDI R3 R3 5", 6, 3, 0, 3, 5));
    Is.push_back(Instruction("BEQ R4, R3, 1", 2, 4, 3, 0, 1));
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
