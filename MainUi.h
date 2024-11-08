//
// Created by HP on 07/11/2024.
//

#ifndef UNTITLED6_MAINUI_H
#define UNTITLED6_MAINUI_H
#include "Machine.h"
#include "iostream"
#include "ALU.h"
#include "Register.h"
#include "Memory.h"
#include "CU.h"
#include <iostream>

using namespace std;


class MainUi {
private:
    Machine machine;
    ALU alu;
    Register reg;
    Memory memory;


//    ins = false, file = true
//    bool enterFileOrInstruction = false;

public:
    void displayMenu();
    char inputChoice();
    vector<string> instructions;

    string inputInstruction();

};


#endif //UNTITLED6_MAINUI_H
