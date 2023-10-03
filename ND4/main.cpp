#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

void INC();
void DEC();
void JZ();
void JNZ();
void JO();

void MOV(unsigned char regs[16], unsigned char constant);
void MOVC(unsigned char regs[16], unsigned char constant);
void IN(unsigned char regs[16], unsigned char constant, char symbol);
void SUB(unsigned char regs[16], unsigned char constant);
void LSL(unsigned char regs[16], unsigned char constant);
void LSR(unsigned char regs[16], unsigned char constant);
void RET(char &eofFlag);
void ADD(unsigned char regs[16], unsigned char constant);
void OR(unsigned char regs[16], unsigned char constant);
void XOR(unsigned char regs[16], unsigned char constant);
void OUT(unsigned char regs[16], unsigned char constant);
void JFE(char constant, int &i, bool eof);
void JMP(unsigned char constant, int &i);

int main() {
    char prog_mem[256], eofFlag = 0b00000000, zeroFlag = 0b00000000, overflowFlag = 0b00000000;
    unsigned char regs[16];
    int i = 0;

    ifstream binFile("decryptor.bin", ios::in | ios::binary);
    ifstream txtFile("q1_encr.txt");
    binFile.read(prog_mem, 32);

    while(eofFlag != 0b00000100) {
        if (prog_mem[i] == 0x01) {

        } else if (prog_mem[i] == 0x02) {
            
        } else if (prog_mem[i] == 0x03) {
            MOV(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x04) {
            MOVC(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x05) {
            LSL(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x06) {
            LSR(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x07) {
            JMP(prog_mem[i + 1], i);
        } else if (prog_mem[i] == 0x08) {
            
        } else if (prog_mem[i] == 0x09) {
            
        } else if (prog_mem[i] == 0x0A) {
            JFE(prog_mem[i + 1], i, txtFile.eof());
        } else if (prog_mem[i] == 0x0B) {
            RET(eofFlag);
        } else if (prog_mem[i] == 0x0C) {
            ADD(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x0D) {
            SUB(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x0E) {
            XOR(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x0F) {
            OR(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x10) {
            IN(regs, prog_mem[i + 1], txtFile.get());
        } else if (prog_mem[i] == 0x11) {
            OUT(regs, prog_mem[i + 1]);
        } else if (prog_mem[i] == 0x12) {
            
        }

        i += 2;
    }

    return 0;
}

void MOVC(unsigned char regs[16], unsigned char constant) {
    regs[0] = constant;
}

void IN(unsigned char regs[16], unsigned char constant, char symbol) {
    regs[static_cast<int>(constant)] = symbol;
}

void SUB(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111, Ry = (constant & 0b00001111) >> 4;
    regs[Rx] = regs[Rx] - regs[Ry];
}

void LSL(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111;
    regs[Rx] = regs[Rx] << 1;
}

void OR(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111, Ry = (constant >> 4) & 0b00001111;
    regs[Rx] = regs[Rx] | regs[Ry];
}

void XOR(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111, Ry = (constant >> 4) & 0b00001111;
    regs[Rx] = regs[Rx] ^ regs[Ry];
}

void OUT(unsigned char regs[16], unsigned char constant) {
    ofstream outFile("output.txt", ios::app);
    char Rx = constant & 0b00001111;
    outFile << regs[Rx];
}

void JFE(char constant, int &i, bool eof) {
    if (eof) {
        if (static_cast<int>(constant) > 31) {
            i += (static_cast<int>(constant)) % 16;
        } else {
            i += (static_cast<int>(constant));
        }

        if (i > 31) {
            i -= 34;
        }
    }
}

void JMP(unsigned char constant, int &i) {
    if (static_cast<int>(constant) > 31) {
        i += (static_cast<int>(constant)) % 16;
    } else {
        i += (static_cast<int>(constant));
    }

    if (i > 31) {
        i -= 34;
    }
}

void RET(char &eofFlag) {
    eofFlag = 0b00000100;
}

void MOV(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111, Ry = (constant >> 4) & 0b00001111;
    regs[Rx] = regs[Ry];
}

void INC(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111;
    regs[Rx] |= 0x01;
}

void DEC(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111;
    regs[Rx] |= 0xFF;
}

void LSR(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111;
    regs[Rx] = regs[Rx] >> 1;
}

void ADD(unsigned char regs[16], unsigned char constant) {
    char Rx = constant & 0b00001111, Ry = (constant & 0b00001111) >> 4;
    regs[Rx] = regs[Rx] + regs[Ry];
}