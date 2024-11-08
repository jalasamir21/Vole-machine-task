//
// Created by HP on 07/11/2024.
//

#include "CPU.h"
int CPU::programCounter = 0;
void CPU::runNextStep(Memory& memory) {
    // Fetch the next instruction from memory using the program counter
    instructionRegister = memory.getCell(programCounter);

    // Decode the instruction into a vector of components (opcode, operands)
    vector<int> decodedInstruction = decode();

    // Execute the decoded instruction
//    string &instruction, Register &reg, Memory &memory, int &instructionPointer
    alu.execute(instructionRegister,reg, memory, programCounter);

    // Increment the program counter to point to the next instruction
    programCounter++;
}
vector<int> CPU::decode() {
    vector<int> decoded;

    // Assume the instruction format is something like:
    // "opcode operand1 operand2", where opcode and operands are integers.

    int opcode = stoi(instructionRegister.substr(0, 2)); // Extract opcode
    int operand1 = stoi(instructionRegister.substr(2, 2)); // Extract first operand
    int operand2 = stoi(instructionRegister.substr(4, 2)); // Extract second operand

    decoded.push_back(opcode);      // Opcode
    decoded.push_back(operand1);    // Operand 1
    decoded.push_back(operand2);    // Operand 2

    return decoded;
}

//void CPU::execute(Register& reg, Memory& memory, string instruction) {
//    int cmd = stoi(instruction[0]);
////    int opcode = vec[0];
////    int operand1 = vec[1];
////    int operand2 = vec[2];
//
//    switch (opcode) {
//        case 1: // LOAD operation
//            cu.load(operand1, alu.hexToDec(memory.getCell(operand2)), reg);
//            break;
//        case 2: // LOAD operation
//            cu.load();
//            break;
//
//        case 3:
//         // STORE operation
//            cu.store(operand1, reg.getCell(operand2), reg, memory);
//
//            break;
//
//        case 4: // ADD operation
//            alu.add(operand1, operand2,);
//            break;
//
//        case 4: // SUBTRACT operation
//            reg.setValue(operand1, alu.subtract(reg.getValue(operand1), reg.getValue(operand2)));
//            break;
//
//        case 5: // JUMP operation
//            if (reg.getValue(operand1) != 0) {
//                programCounter = operand2; // Update program counter if condition is met
//            }
//            break;
//
//        case 6: // HALT operation
//            cout << "Program halted." << endl;
//            exit(0);
//            break;
//
//        default:
//            cout << "Unknown opcode: " << opcode << endl;
//            break;
//    }
//}
//
