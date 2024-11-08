//
// Created by HP on 07/11/2024.
//

#include "ALU.h"
#include <set>
#include <sstream>
#include <bitset>
#include <cmath>
using namespace std;

int ALU::hexToDec(string hexVal) {
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

            // if character lies in 'A'-'F' , converting
            // it to integral 10 - 15 by subtracting 55
            // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;

}
float ALU::prepareAddFloat(string hexValue) {
    int decimalValue = hexToDec(hexValue);
    if (decimalValue <= 15) {
        string binaryValue = decToBin(decimalValue);
        while (binaryValue.length() < 4) {
            binaryValue = "0" + binaryValue;
        }
        string binaryRep = "0.0000" + binaryValue;
        float sumOfFloats = 0.0;
        int exponent = -5;

        for (int i = 6; i < binaryRep.length(); i++) {
            if (binaryRep[i] == '1') {
                sumOfFloats += pow(2, exponent);
            }
            exponent--;
        }
        return sumOfFloats;
    } else {
        char firstChar = hexValue[0];
        char secondChar = hexValue[1];
        int firstDecimal = hexFormat(firstChar);
        int secondDecimal = hexFormat(secondChar);
        if (firstDecimal <= 7) {
            int exponent = firstDecimal - 4;
            if (exponent <= 0) {
                exponent = -exponent;
                string binaryRep = "0.";
                for (int i = 0; i < exponent; i++) {
                    binaryRep+= "0";
                }
                string binaryValue = decToBin(secondDecimal);
                while (binaryValue.length() < 4) {
                    binaryValue = "0" + binaryValue;
                }
                binaryRep += binaryValue;
                float sum = 0;
                int c = 0;
                for (int i = 0; i < binaryRep.length(); i++) {
                    if (binaryRep[i] == '1') {
                        sum += pow(2, c);
                        c--;
                    } else if (binaryRep[i] == '.') {
                        continue;
                    } else {
                        c--;
                    }
                }
                return sum;
            } else {
                string binaryValue = decToBin(secondDecimal);
                while (binaryValue.length() < 4) {
                    binaryValue = "0" + binaryValue;
                }
                string binaryRepresentation = "0." + binaryValue;
                int c = exponent;
                float sum = 0;
                for (int i = 0; i < binaryRepresentation.length(); i++) {
                    if (binaryRepresentation[i] == '1') {
                        sum += pow(2, c);
                        c--;
                    } else if (binaryRepresentation[i] == '.') {
                        continue;
                    } else {
                        c--;
                    }
                }
                return sum;
            }
        } else {
            string binaryValue = decToBin(firstDecimal);
            string binaryRepresentation;
            for (int i = 1; i < binaryValue.length(); i++) {
                binaryRepresentation += binaryValue[i];
            }
            int exponent = firstDecimal - 8;
            int adjustedExponent = exponent - 4;
            if (adjustedExponent <= 0) {
                adjustedExponent = -adjustedExponent;
                string binaryRepresentation = "0.";
                for (int i = 0; i < adjustedExponent; i++) {
                    binaryRepresentation += "0";
                }
                string binaryValue = decToBin(secondDecimal);
                while (binaryValue.length() < 4) {
                    binaryValue = "0" + binaryValue;
                }
                binaryRepresentation += binaryValue;
                float sum = 0;
                int c = 0;
                for (int i = 0; i < binaryRepresentation.length(); i++) {
                    if (binaryRepresentation[i] == '1') {
                        sum += pow(2, c);
                        c--;
                    } else if (binaryRepresentation[i] == '.') {
                        continue;
                    } else {
                        c--;
                    }
                }
                return -sum;
            } else {
                string binaryValue = decToBin(secondDecimal);
                while (binaryValue.length() < 4) {
                    binaryValue = "0" + binaryValue;
                }
                string binaryRepresentation = "0." + binaryValue;
                int c = adjustedExponent;
                float sum = 0;
                for (int i = 0; i < binaryRepresentation.length(); i++) {
                    if (binaryRepresentation[i] == '1') {
                        sum += pow(2, c);
                        c--;
                    } else if (binaryRepresentation[i] == '.') {
                        continue;
                    } else {
                        c--;
                    }
                }
                return -sum;
            }
        }
    }
}
string ALU::add(string hexA, string hexB) {
    int decimalA = prepareAdd(hexA);
    int decimalB = prepareAdd(hexB);
    int sum = decimalA + decimalB;
    if (sum > 0) {
        return decToHex(sum);
    } else {
        sum = -sum;
        sum--;
        string binarySum = decToBin(sum);
        int padding = 8 - binarySum.length();
        for (int i = 0; i < padding; i++) {
            binarySum = "0" + binarySum;
        }
        for (int i = 0; i < 8; i++) {
            if (binarySum[i] == '1') {
                binarySum[i] = '0';
            } else {
                binarySum[i] = '1';
            }
        }

        int c = 7;
        int result = 0;
        for (int i = 0; i < binarySum.length(); i++) {
            if (binarySum[i] == '1') {
                result += pow(2, c);
            }
            c--;
        }

        return decToHex(result);
    }
}

string ALU :: decToBin(int dec) {
    if (dec == 0) return "0";

    string bin;
    while (dec > 0) {
        bin = (dec % 2 == 0 ? "0" : "1") + bin;
        dec /= 2;
    }
    return bin;
}
int ALU::prepareAdd(string hexValue) {
    int decimalValue = hexToDec(hexValue);
    string binaryValue = decToBin(decimalValue);
    if (decimalValue <= 15) {
        return decimalValue;
    } else {
        char firstChar = hexValue[0];
        int firstDecimal = hexFormat(firstChar);
        if (firstDecimal <= 7) {
            int sum = 0;
            int bitPosition = binaryValue.length() - 1;
            for (int i = 0; i < binaryValue.length(); i++) {
                if (binaryValue[i] == '1') {
                    sum += pow(2, bitPosition);
                }
                bitPosition--;
            }
            return sum;
        } else {
            int sum = 0;
            int bitPosition = binaryValue.length() - 1;
            for (int i = 0; i < binaryValue.length(); i++) {
                if (binaryValue[i] == '0') {
                    binaryValue[i] = '1';
                } else {
                    binaryValue[i] = '0';
                }
            }
            for (int i = 0; i < binaryValue.length(); i++) {
                if (binaryValue[i] == '1') {
                    sum += pow(2, bitPosition);
                }
                bitPosition--;
            }
            return -(sum + 1);
        }
    }
}
string ALU::integerToBin(int integer) {
    if (integer == 0) return "0";

    string binary;
    while (integer > 0) {
        binary = (integer % 2 == 0 ? "0" : "1") + binary;
        integer /= 2;
    }
    return binary;
}
string ALU::fractToBin(float fractionalValue) {
    string binaryFraction;
    while (fractionalValue > 0) {
        fractionalValue *= 2;
        if (fractionalValue >= 1) {
            binaryFraction += "1";
            fractionalValue -= 1;
        } else {
            binaryFraction += "0";
        }
    }
    return binaryFraction;
}
int ALU::hexFormat(char hexChar) {
    if (hexChar >= '0' && hexChar <= '9') {
        return hexChar - '0';
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return hexChar - 'A' + 10;
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return hexChar - 'a' + 10;
    }
    return 0;
}
string ALU::floatToBin(float floatValue) {
    int intPart = static_cast<int>(floatValue);
    float fractionalPart = floatValue - intPart;
    string binInt = integerToBin(intPart);
    string binFract = fractToBin(fractionalPart);
    return binInt + "." + binFract;
}
string ALU::addFloat(string hexA, string hexB) {
    float floatA = prepareAddFloat(hexA);
    float floatB = prepareAddFloat(hexB);
    float sum = floatA + floatB;
    cout << sum << endl;
    int exponent = 0;
    if (sum >= 1) {
        string binarySum = floatToBin(sum);
        for (int i = 0; i < binarySum.length(); i++) {
            if (binarySum[i] == '.') {
                exponent = i;
            }
        }
        exponent += 4;
        string hexExponent = decToHex(exponent);
        int c = 0;
        int result = 0;
        int power = 3;
        for (int i = 0; i < binarySum.length(); i++) {
            if (c == 4) {
                break;
            } else if (binarySum[i] == '.') {
                continue;
            } else {
                if (binarySum[i] == '1') {
                    result += pow(2, power);
                }
                c++;
                power--;
            }
        }
        hexExponent += decToHex(result);
        return hexExponent;
    } else if (sum <= -1) {
        sum = -sum;
        string binarySum = floatToBin(sum);
        for (int i = 0; i < binarySum.length(); i++) {
            if (binarySum[i] == '.') {
                exponent = i;
            }
        }
        exponent += 4;
        string binaryExponent = "1" + decToBin(exponent);
        int result = 0;
        int power = 3;
        for (int i = 0; i < 4; i++) {
            if (binaryExponent[i] == '1') {
                result += pow(2, power);
            }
            power--;
        }

        string hexExponent = decToHex(result);
        int c = 0;
        result = 0;
        power = 3;
        for (int i = 0; i < binarySum.length(); i++) {
            if (c == 4) {
                break;
            } else if (binarySum[i] == '.') {
                continue;
            } else {
                if (binarySum[i] == '1') {
                    result += pow(2, power);
                }
                c++;
                power--;
            }
        }
        hexExponent += decToHex(result);
        return hexExponent;
    } else if ((sum > 0) && (sum < 1)) {
        string binarySum = floatToBin(sum);
        int firstOneIndex = 0;
        for (int i = 0; i < binarySum.length(); i++) {
            if (binarySum[i] == '1') {
                firstOneIndex = i;
                break;
            }
        }
        int exponent = firstOneIndex - 2;
        exponent = -exponent;
        exponent += 4;
        if (exponent < 0) {
            exponent = 0;
        }
        string hexExponent = decToHex(exponent);
        int result = 0;
        int power = 3;
        for (int i = firstOneIndex; i < (firstOneIndex + 4); i++) {
            if (binarySum[i] == '1') {
                result += pow(2, power);
            }
            power--;
        }
        hexExponent += decToHex(result);
        return hexExponent;
    } else {
        sum = -sum;
        string binarySum = floatToBin(sum);
        int firstOneIndex = 0;
        for (int i = 0; i < binarySum.length(); i++) {
            if (binarySum[i] == '1') {
                firstOneIndex = i;
                break;
            }
        }
        int exponent = firstOneIndex - 2;
        exponent = -exponent;
        exponent += 4;
        if (exponent < 0) {
            exponent = 0;
        }
        exponent += 8;
        string hexExponent = decToHex(exponent);
        int result = 0;
        int power = 3;
        for (int i = firstOneIndex; i < (firstOneIndex + 4); i++) {
            if (binarySum[i] == '1') {
                result += pow(2, power);
            }
            power--;
        }
        hexExponent += decToHex(result);
        return hexExponent;
    }
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
    string hexA = decToHex(reg.getCell(x2));
    string hexB = decToHex(reg.getCell(x3));
    string result = add(hexA, hexB);
    reg.setCell(x1, hexToDec(result));


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

void ALU::execute(string &instruction, Register &reg, Memory &memory, int instructionPointer) {
    cout << "Executing instruction: " << instruction << endl;
    string opcode = "0x" + instruction.substr(0, 1);
    int destinationIdx = hexToDec(instruction.substr(1, 1));
    int srcIdx1 = hexToDec(instruction.substr(2, 1));
    int srcIdx2 = hexToDec(instruction.substr(3, 1));
    int memAddress = hexToDec(instruction.substr(2, 2));
    int value = hexToDec(instruction.substr(2, 2)); // Extract the value for load2

    if (opcode == "0x1") {
        load1(destinationIdx, memAddress, reg, memory);
    } else if (opcode == "0x2") {
        load2(destinationIdx, value, reg); // Use the extracted value for load2
    } else if (opcode == "0x3") {
        store(destinationIdx, memAddress, reg, memory);
    } else if (opcode == "0x4") {
        move(srcIdx2, srcIdx1, reg);
    } else if (opcode == "0x5") {
        add(destinationIdx, srcIdx1, srcIdx2, reg);
    } else if (opcode == "0x6") {
        addFloat(destinationIdx, srcIdx1, srcIdx2, reg);
    } else if (opcode == "0x7") {
        Or(destinationIdx, srcIdx1, srcIdx2, reg);
    } else if (opcode == "0x8") {
        And(destinationIdx, srcIdx1, srcIdx2, reg);
    } else if (opcode == "0x9") {
        Xor(destinationIdx, srcIdx1, srcIdx2, reg);
    } else if (opcode == "0xA") {
        rotate(destinationIdx, value, reg);
    } else if (opcode == "0xB") {
        jump(destinationIdx, memAddress, reg, instructionPointer);
    } else if (opcode == "0xC") {
        halt();
    }
}
// Arithmetic and logical operations
void ALU::load1(int destinationIdx, int memAddress, Register &reg, Memory &memory)
{
    int vALUe = hexToDec(memory.getCell(memAddress));
    reg.setCell(destinationIdx, vALUe);
}

void ALU:: load2(int destinationIdx, int vALUe, Register &reg) {
    // Check if the value is a floating point


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
    string hexA = decToHex(reg.getCell(srcIdx1));
    string hexB = decToHex(reg.getCell(srcIdx2));
    string result = addFloat(hexA, hexB);
    reg.setCell(destinationIdx, hexToDec(result));
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
void ALU::store(int srcIdx, int address, Register &reg, Memory &memory) {
    int value = reg.getCell(srcIdx);
    memory.setCell(address, decToHex(value));
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




