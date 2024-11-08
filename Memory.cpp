//
// Created by HP on 07/11/2024.
//

#include "Memory.h"

void Memory::setCell(int address, string value) {
    memory[address] = value;

}

string Memory::getCell(int address) {
    return memory[address];
}

Memory::Memory() {

    for (int i = 0; i < size; ++i) {
        memory[i] = "00";
    }


}
