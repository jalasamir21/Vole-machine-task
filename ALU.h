//
// Created by HP on 07/11/2024.
//

#ifndef UNTITLED6_ALU_H
#define UNTITLED6_ALU_H
#include "iostream"
#include "Register.h"
#include "CU.h"
using namespace std;


class ALU {


public:
    int hexToDec(string hexVal);
    string decToHex(int value);
    bool isValid(string value);
    void add(int x1, int x2, int x3, Register& reg);
    void jump(int regIdx, int memAddress, Register &reg, int &instructionPointer);
    float prepareAddFloat(string hexValue);
    int prepareAdd(string hexValue);
    string integerToBin(int integer);
    string fractToBin(float fractionalValue);
    int hexFormat(char hexChar);
    string floatToBin(float floatValue);
    string add(string hexA, string hexB);
    string decToBin(int dec);
    string addFloat(string hexA, string hexB);
    void execute(string &instruction, Register &reg, Memory &memory, int instructionPointer);

    void rotate(int regIdx, int numBits, Register &reg);

    void Xor(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg);

    void And(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg);

    void Or(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg);

    void addFloat(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg);

    void move(int destinationIdx, int srcIdx, Register &reg);

//    void store(int srcIdx, int address, Memory &memory, Register &reg);

    void load2(int destinationIdx, int vALUe, Register &reg);

    void load1(int destinationIdx, int memAddress, Register &reg, Memory &memory);

    void load(int idxReg, int val, Register& reg);
    void store(int idxReg, int idxMem, Register& reg, Memory& memory);
//    void move(int idxReg1, int idxReg2, Register& reg);
//    void jump(int idxReg1, int idxMem, Register& reg, int& Pc);
    int halt();


    void load(int idxReg, Register &reg, Memory &memory);
};


#endif //UNTITLED6_ALU_H
