//
// Created by HP on 07/11/2024.
//


#ifndef UNTITLED6_MEMORY_H
#define UNTITLED6_MEMORY_H
#include <iostream>
using namespace std;


class Memory {
private:
    int size = 256;
    string memory[256] = {"00"};
public:
    Memory();
    string getCell(int address);
    void setCell(int address, string value);

};


#endif //UNTITLED6_MEMORY_H
