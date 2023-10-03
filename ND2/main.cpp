#include <iostream>
#include <bitset>

using namespace std;

void ALU(bitset<8> a, bitset<8> b, int carry_in, int carry_out, int ENA, int ENB, bitset<3> INPUT);
int NAND(int a, int b);
int OR(int a, int b);
int AND(int a, int b);
int NOT(int a);
int XOR(int a, int b);
int NOR(int a, int b);
bitset<8> DECODER(bitset<3> INPUT);
int HALFADDER(int a, int b, int &carry);
int FULLADDER(int a, int b, int &carry);
bitset<8> ADDER(bitset<8> a, bitset<8> b);
bitset<8> ATIMTIS(bitset<8> b, bitset<8> a);
bitset<8> DAUGYBA(bitset<8> a, bitset<8> b);
bitset<8> SHIFT(bitset<8> b, int carry_in);
bitset<8> PLUSONE(bitset<8> b);
bitset<1> EQUAL(bitset<8> b);
void ENABLE(bitset<8> &x, int EN);

int main() {
    int carry_in = 1, carry_out = 0, ENA = 1, ENB = 1;
    bitset<3> INPUT("000");
    bitset<8> a("10101000");
	bitset<8> b("10101001");

    ALU(a, b, carry_in, carry_out, ENA, ENB, INPUT);

    return 0;
}

int NAND(int a, int b) {
    if (a == 0 && b == 0) {
		return 1;
	}
	if (a == 0 && b == 1) {
		return 1;
	}
	if (a == 1 && b == 0) {
		return 1;
	}
	if (a == 1 && b == 1) {
		return 0;
	}
}

int OR(int a, int b) {
    return NAND(NAND(a, a), NAND(b, b));
}

int AND(int a, int b) {
    return NAND(NAND(a, b), NAND(a, b));
}

int NOT(int a) {
    return NAND(a, a);
}

int XOR(int a, int b) {
    return NAND(NAND(a, NAND(a, b)), NAND(b, NAND(a, b)));
}

int NOR(int a, int b) {
    return NAND(a, b);
}

bitset<8> DECODER(bitset<3> INPUT) {
    bitset<8> DCode;
    DCode[7] = AND(AND(NOT(INPUT[2]), NOT(INPUT[1])), NOT(INPUT[0])); 
    DCode[6] = AND(AND(NOT(INPUT[2]), NOT(INPUT[1])), INPUT[0]); 
    DCode[5] = AND(AND(NOT(INPUT[2]), INPUT[1]), NOT(INPUT[0]));
    DCode[4] = AND(AND(NOT(INPUT[2]), INPUT[1]), INPUT[0]);
    DCode[3] = AND(AND(INPUT[2], NOT(INPUT[1])), NOT(INPUT[0]));
    DCode[2] = AND(AND(INPUT[2], NOT(INPUT[1])), INPUT[0]);
    DCode[1] = AND(AND(INPUT[2], INPUT[1]), NOT(INPUT[0]));
    DCode[0] = AND(AND(INPUT[2], INPUT[1]), INPUT[0]);
    return DCode;
}

int HALFADDER(int a, int b, int &carry) {
    carry = AND(a, b);
    return XOR(a, b);
}

int FULLADDER(int a, int b, int &carry) {
    int carry1, carry2, sum;
    sum = HALFADDER(HALFADDER(a, b, carry1), carry, carry2);
    carry = OR(carry1, carry2);
    return sum;
}

bitset<8> ADDER(bitset<8> a, bitset<8> b) {
    int carry = 0;
    bitset<8> vsum;
    for (int i = 0; i < 8; i++) {
        vsum[i] = FULLADDER(a[i], b[i], carry);
    }
    return vsum;
}

bitset<8> DAUGYBA(bitset<8> a, bitset<8> b) {
    bitset<8> vsum, shifted = a;
    for (int i = 0; i < 8; i++) {
        if (i != 0) {
            shifted = SHIFT(shifted, 0);
        }
        if (b[i] == 1) {
            vsum = ADDER(vsum, shifted);
        }
    }
    return vsum;
}

bitset<8> ATIMTIS(bitset<8> b, bitset<8> a) {
    bitset<8> c;
    for (int i = 0; i < 8; i++) {
        c[i] = NOT(a[i]);
    }
    return ADDER(PLUSONE(c), b);
}

bitset<8> SHIFT(bitset<8> b, int carry_in) {
    bitset<8> bnew;
    bnew[7] = AND(b[6], NOT(carry_in));
    bnew[6] = OR(AND(b[7], carry_in), AND(b[5], NOT(carry_in)));
    bnew[5] = OR(AND(b[6], carry_in), AND(b[4], NOT(carry_in)));
    bnew[4] = OR(AND(b[5], carry_in), AND(b[3], NOT(carry_in)));
    bnew[3] = OR(AND(b[4], carry_in), AND(b[2], NOT(carry_in)));
    bnew[2] = OR(AND(b[3], carry_in), AND(b[1], NOT(carry_in)));
    bnew[1] = OR(AND(b[2], carry_in), AND(b[0], NOT(carry_in)));
    bnew[0] = AND(b[1], carry_in);

    return bnew;
}

bitset<8> PLUSONE(bitset<8> b) {
    bitset<8> x = b;
    for (int i = 0; i < 8; i++) {
        if (x[i] == 1) {
            x[i] = NOT(x[i]);
        } else {
            x[i] = NOT(x[i]);
            break;
        }
    }
    return x;
}

bitset<1> EQUAL(bitset<8> b) {
    bitset<1> a("0"), ats;
    for (int i = 0; i < 8; i++) {
        ats[i] = OR(AND(NOT(b[i]), NOT(a[i])), AND(b[i], a[i]));
    }
    for (int i = 0; i < 8; i++) {
        if (ats[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void ENABLE(bitset<8> &x, int EN) {
    if (EN == 0) {
        for (int i = 0; i < 8; i++) {
            if (x[i] == 1) {
                x[i] = NOT(x[i]);
            }
        }
    }
}

void ALU(bitset<8> a, bitset<8> b, int carry_in, int carry_out, int ENA, int ENB, bitset<3> INPUT) {
    bitset<8> OUTPUT = DECODER(INPUT);
    ENABLE(a, ENA);
    ENABLE(b, ENB);
    if (OUTPUT[7] == 1) {
        cout << b << " - " << a << " = " << ATIMTIS(b, a) << endl; // 000. B - A.
    }
    if (OUTPUT[6] == 1) {
        cout << a << " + " << b << " = " << ADDER(a, b) << endl; // 001. A + B.
    }
    if (OUTPUT[5] == 1) {
        cout << a << " * " << b << " = " << DAUGYBA(a, b) << endl; // 010. A * B.
    }
    if (OUTPUT[4] == 1) {
        cout << b << " >> 1 = " << SHIFT(b, carry_in) << endl; // carry_in = 1 | 011. B >> 1
    }
    if (OUTPUT[3] == 1) {
        cout << b << " + 1 = " << PLUSONE(b) << endl; // 100. B + 1.
    }
    if (OUTPUT[2] == 1) {
        cout << b << " == 0 : " << EQUAL(b) << endl; // 101. B == 0.
    }
    if (OUTPUT[1] == 1 || OUTPUT[0] == 1) {
        cout << INPUT << " Isejo uz registro limito, programa nutraukta" << endl;
    }
}