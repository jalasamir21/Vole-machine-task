//
// Created by HP on 07/11/2024.
//

#ifndef UNTITLED6_MACHINE_H
#define UNTITLED6_MACHINE_H
#include "CPU.h"
#include "ALU.h"
#include "Register.h"


#include "Memory.h"



class Machine {
    private:
    CPU processor;
    Memory memory;
    ALU alu;
    Register reg;
    vector<string>instructions;
    public:
    void loadProgramFile(vector<string>& instructions);
    void outputstate();
    void outputInstructions(vector<string>& instruction);

};


#endif //UNTITLED6_MACHINE_H
