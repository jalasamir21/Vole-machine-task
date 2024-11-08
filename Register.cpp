//
// Created by HP on 07/11/2024.
//

#include "Register.h"
Register::Register() {
    for (int i = 0; i < 16; ++i) {
        memory[i] = 0;
    }
}
void Register::setCell(int address, int value) {
    memory[address] = value;

}

int Register::getCell(int address) {
    return memory[address];
}
