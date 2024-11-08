//
// Created by HP on 07/11/2024.
//

#ifndef UNTITLED6_CPU_H
#define UNTITLED6_CPU_H
#include "ALU.h"
#include "Register.h"
#include "Memory.h"
#include "CU.h"
#include <iostream>
#include <vector>

using namespace std;


class CPU {
    private:
    string instructionRegister;
    ALU alu;
    Register reg;
//    void runNextStep(Memory& memory);
    vector<int> decode();
//    void execute(Register& reg, Memory& memory, string instruction);
    public:
    void runNextStep(Memory& memory);
    static int programCounter;


};


#endif //UNTITLED6_CPU_H
