//
// Created by HP on 07/11/2024.
//

#include "MainUi.h"

string MainUi::inputInstruction() {
    string instruction;
    cout << "Enter instruction: ";
    cin >> instruction;
    return instruction;
}


char MainUi::inputChoice() {
    char c;
    cin >> c;
    return c;
}

void MainUi::displayMenu() {
    vector<Memory> memories(256);
    vector<Register> registers(16);
    char c;
    do {
        cout << "\n--- CPU Simulation Menu ---\n";
        cout << "1. Load file\n";
        cout << "2. Display State\n";
        cout << "3. Enter Instruction\n";
        cout << "4. Execute Program\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        c = inputChoice();
        string instruction;

        switch (c) {
            case '1':
                machine.loadProgramFile(instructions);
                break;
            case '2':
                machine.outputInstructions(instructions);
                break;
            case '3':
                instruction = inputInstruction();
                alu.execute(instruction, reg, memory, 0);
                break;
            case '4':
                machine.outputstate();

                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (c != '4');
}





