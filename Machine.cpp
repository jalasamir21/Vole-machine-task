//
// Created by HP on 07/11/2024.
//

#include "Machine.h"
#include <iomanip>
#include <fstream>
void Machine::loadProgramFile(vector<string>& instructions) {
    fstream file;
    string line;
    cout << "Enter filename";
    string filename;
    cin >> filename;
    file.open(filename, ios::in);
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
//        fileIsLoad = false;
    }
    int i = 0;
    while (getline(file, line))
    {
        instructions.push_back(line);
//        string &instruction, Register &reg, Memory &memory, int instructionPointer
        alu.execute(line, reg, memory, CPU::programCounter);
        memory.setCell(i, line.substr(0, 2));

        memory.setCell(i + 1, line.substr(2, 4));
        i += 2;
    }
    file.close();


}

void Machine::outputstate() {
//    cout << "Program Counter: " << processor.getProgramCounter() << endl;
//    cout << "Instruction Register: " << processor.getInstructionRegister() << endl;

    cout << "\nMemory:\n";
    for (size_t i = 0; i < 256; ++i) {
//        cout << std::setw(4) << std::hex << memories[i] << " | ";
        cout <<setw(3)<<  alu.decToHex(i) << "| "<< memory.getCell(i);
        if ((i + 1) % 16 == 0) std::cout << "\n";
    }
    cout << "Registers:\n";
    for (size_t i = 0; i < 16; ++i) {
        cout << "Register " << i << "  :  " << reg.getCell(i) << endl; // Assuming getValue() fetches the stored value.
    }

}
void Machine::outputInstructions(vector<string> &instructions){
    for(int i = 0; i< instructions.size(); ++i){
        cout << "PC: " << i << "   instruction: "<< instructions[i] << endl;
    }

}


