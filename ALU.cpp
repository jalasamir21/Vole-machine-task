//
// Created by HP on 07/11/2024.
//

#include "ALU.h"
#include <set>
using namespace std;

int ALU::hexToDec(string vALUe) {
    int len = vALUe.size();

    // Initializing base vALUe to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII vALUe
        if (vALUe[i] >= '0' && vALUe[i] <= '9')
        {
            dec_val += (int(vALUe[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

            // if character lies in 'A'-'F' , converting
            // it to integral 10 - 15 by subtracting 55
            // from ASCII vALUe
        else if (vALUe[i] >= 'A' && vALUe[i] <= 'F')
        {
            dec_val += (int(vALUe[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;

}

string ALU::decToHex(int vALUe) {
    string hexa = "";

    while (vALUe != 0)
    {
        // remainder variable to store remainder
        int rem = 0;

        // ch variable to store each character
        char ch;
        // storing remainder in rem variable.
        rem = vALUe % 16;

        // check if temp < 10
        if (rem < 10)
        {
            ch = rem + 48;
        }
        else
        {
            ch = rem + 55;
        }

        // updating the ans string with the character variable
        hexa += ch;
        vALUe = vALUe / 16;
    }

    // reversing the ans string to get the final result
    int i = 0, j = hexa.size() - 1;
    while (i <= j)
    {
        swap(hexa[i], hexa[j]);
        i++;
        j--;
    }
    return hexa;
}

void ALU::add(int x1, int x2, int x3, Register &reg) {
    string sx1 = to_string(reg.getCell(x1));
    string sx2 = to_string(reg.getCell(x2));
    reg.setCell(x3, x1 + x2);

}




// Validates if the input is in a correct format for the ALU operations
bool ALU::isValid(string vALUe)
{
    if (vALUe.length() != 4)
    {
        return false; // Must be exactly 4 characters
    }

    if (vALUe.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos)
    {
        return false; // Contains invalid characters
    }

    // Map of valid single-character opcodes
    std::set<char> opcodes = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

    // Check if the first character (opcode) is valid
    if (opcodes.find(vALUe[0]) == opcodes.end())
    {
        return false; // Opcode is not valid
    }

    return true; // Valid input
}

void ALU::execute(string &instruction, Register &reg, Memory &memory, int instructionPointer)
{
    // Extract the opcode and the parameters

    string opcode = "0x" + instruction.substr(0, 1);
    int destinationIdx = hexToDec(instruction.substr(1, 1));
    int srcIdx1 = hexToDec(instruction.substr(2, 1));
    int srcIdx2 = hexToDec(instruction.substr(3, 1));
    int memAddress = hexToDec(instruction.substr(2, 2));


    // Map opcodes to methods
    if (opcode == "0x1") // LOAD
    {
        load1(destinationIdx, memAddress, reg, memory);
    }
    else if (opcode == "0x2") // LOAD immediate
    {
        load2(destinationIdx, memAddress, reg);
    }
    else if (opcode == "0x3") // STORE
    {
        store(srcIdx1, memAddress, reg,memory);
    }
    else if (opcode == "0x4") // MOVE
    {
        move(destinationIdx, srcIdx1, reg);
    }
    else if (opcode == "0x5") // ADD
    {
        add(destinationIdx, srcIdx1, srcIdx2, reg);
    }
    else if (opcode == "0x6") // ADD FLOAT
    {
        addFloat(destinationIdx, srcIdx1, srcIdx2, reg);
    }
    else if (opcode == "0x7") // OR
    {
        Or(destinationIdx, srcIdx1, srcIdx2, reg);
    }
    else if (opcode == "0x8") // AND
    {
        And(destinationIdx, srcIdx1, srcIdx2, reg);
    }
    else if (opcode == "0x9") // XOR
    {
        Xor(destinationIdx, srcIdx1, srcIdx2, reg);
    }
    else if (opcode == "0xA") // ROTATE
    {
        rotate(destinationIdx, srcIdx1, reg);
    }
    else if (opcode == "0xB") // JUMP
    {
        jump(destinationIdx, memAddress, reg, instructionPointer);
    }
    else if (opcode == "0xC") // HALT
    {
        halt();
    }
}
// Arithmetic and logical operations
void ALU::load1(int destinationIdx, int memAddress, Register &reg, Memory &memory)
{
    int vALUe = hexToDec(memory.getCell(memAddress));
    reg.setCell(destinationIdx, vALUe);
}

void ALU::load2(int destinationIdx, int vALUe, Register &reg)
{
    reg.setCell(destinationIdx, vALUe);
}

//void ALU::store(int srcIdx, int address, Memory &memory, Register &reg)
//{
//    memory.setCell(address, std::to_string(reg.getCell(srcIdx)));
//}

void ALU::move(int destinationIdx, int srcIdx, Register &reg)
{
    int vALUe = reg.getCell(srcIdx);
    reg.setCell(destinationIdx, vALUe);
}


void ALU::addFloat(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg)
{
    int intVALUe1 = reg.getCell(srcIdx1);
    int intVALUe2 = reg.getCell(srcIdx2);
    float x1 = *reinterpret_cast<float *>(&intVALUe1);
    float x2 = *reinterpret_cast<float *>(&intVALUe2);
    float result = x1 + x2;
    reg.setCell(destinationIdx, *reinterpret_cast<int *>(&result));
}

void ALU::Or(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg)
{
    int x1 = reg.getCell(srcIdx1);
    int x2 = reg.getCell(srcIdx2);
    reg.setCell(destinationIdx, x1 | x2);
}

void ALU::And(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg)
{
    int x1 = reg.getCell(srcIdx1);
    int x2 = reg.getCell(srcIdx2);
    reg.setCell(destinationIdx, x1 & x2);
}

void ALU::Xor(int destinationIdx, int srcIdx1, int srcIdx2, Register &reg)
{
    int x1 = reg.getCell(srcIdx1);
    int x2 = reg.getCell(srcIdx2);
    reg.setCell(destinationIdx, x1 ^ x2);
}

void ALU::rotate(int regIdx, int numBits, Register &reg)
{
    int vALUe = reg.getCell(regIdx);
    numBits = numBits % 16;
    int rotatedVALUe = (vALUe >> numBits) | (vALUe << (16 - numBits));
    reg.setCell(regIdx, rotatedVALUe);
}



void ALU::load(int idxReg, int val, Register &reg) {
    reg.setCell(idxReg, val);

}
void ALU::store(int idxReg, int idxMem, Register& reg, Memory& memory) {
    // Get the value from the specified register
    int value = reg.getCell(idxReg);

    // Store the value in the specified memory location
    memory.setCell(idxMem, reinterpret_cast<const char *>(value));
}

void ALU:: jump(int idxReg1, int idxMem, Register& reg, int& Pc) {
    // Get the value from the register at idxReg1
    int value = reg.getCell(idxReg1);

    // If the value meets the condition (e.g., is non-zero), update the program counter
    if (value != 0) { // Example condition
        Pc = idxMem;
    }
}

int ALU::halt() {
    cout << "CPU halted." << endl;
    return 0;
}

void ALU::load(int idxReg, Register &reg, Memory& memory) {
    reg.setCell(idxReg, hexToDec(memory.getCell(idxReg)));

}




