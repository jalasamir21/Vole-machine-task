//
// Created by HP on 07/11/2024.
//

#ifndef UNTITLED6_REGISTER_H
#define UNTITLED6_REGISTER_H
#include "Memory.h"


class Register {
    private:
    int memory[16];
    int size = 16;
public:
    Register();
    int getCell(int address);
    void setCell(int address, int value);

};


#endif //UNTITLED6_REGISTER_H
