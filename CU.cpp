//
// Created by HP on 07/11/2024.
//

#include "CU.h"

//void CU::load(int idxReg, Register &reg, Memory &memory) {
//    reg.setCell(idxReg, memory.getCell(idxMem));
//
//
//}

//void CU::load(int idxReg, int val, Register &reg) {
//    reg.setCell(idxReg, val);
//
//}
//void CU::store(int idxReg, int idxMem, Register& reg, Memory& memory) {
//    // Get the value from the specified register
//    int value = reg.getCell(idxReg);
//
//    // Store the value in the specified memory location
//    memory.setCell(idxMem, reinterpret_cast<const char *>(value));
//}
//void CU:: move(int idxReg1, int idxReg2, Register& reg) {
//    // Get the value from the first register
//    int value = reg.getCell(idxReg1);
//
//    // Set that value to the second register
//    reg.setCell(idxReg2, value);
//}
//void CU:: jump(int idxReg1, int idxMem, Register& reg, int& Pc) {
//    // Get the value from the register at idxReg1
//    int value = reg.getCell(idxReg1);
//
//    // If the value meets the condition (e.g., is non-zero), update the program counter
//    if (value != 0) { // Example condition
//        Pc = idxMem;
//    }
//}
//
//int CU::halt() {
//    cout << "CPU halted." << endl;
//
//    return 0;
//}
//
//void CU::load(int idxReg, Register &reg, Memory& memory) {
//    reg.setCell(idxReg, alu.hexToDec(memory.getCell(idxReg)));
//
//}
//
//
