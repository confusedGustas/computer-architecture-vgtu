#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <bitset>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

vector<unsigned char> decimalToUnicode(int decimal);
vector<unsigned char> decimalToUtf8(int decimal);

int main(int argc, char **argv) {
    ofstream df("output.txt");

    if (argc <= 1 || stoi(argv[1]) > 0x10FFFF) {
        ifstream inf("386intel.txt");
        ifstream cpinf("cp437.txt");
        int cp[256];

        for(int i = 0; i < 256; i++) {
            cpinf >> hex >> cp[i];
        }

        while (!inf.eof()) {
            unsigned char symbol = inf.get();
            int unicode = cp[symbol];
            vector <unsigned char> temp = decimalToUtf8(unicode);
            
            copy(temp.begin(), temp.end(), ostream_iterator<unsigned char>(df));
        }
    } else {
        int input = stoi(argv[1]);
        vector<unsigned char> temp1 = decimalToUnicode(input);
        vector<unsigned char> temp2 = decimalToUtf8(input);
        stringstream ss;

        for (auto i : temp1) {
            ss << hex << uppercase << static_cast<int>(i);
        }

        df << "U+" << setfill('0') << setw(4) << uppercase << ss.str() << endl;
        copy(temp2.begin(), temp2.end(), ostream_iterator<int>(df << hex << uppercase, " "));
        df << endl;
        copy(temp2.begin(), temp2.end(), ostream_iterator<char>(df));
    }

    return 0;
}

vector<unsigned char> decimalToUnicode(int decimal) {
    vector<unsigned char> uniBytes;

    if (decimal <= 0x7F) {
        uniBytes.push_back(decimal & 0b11111111);
    } else if (decimal <= 0x7FF) {
        uniBytes.push_back((decimal >> 8) & 0b11111111);
        uniBytes.push_back(decimal & 0b11111111);
    } else if (decimal <= 0xFFFF) {
        uniBytes.push_back((decimal >> 16) & 0b11111111);
        uniBytes.push_back((decimal >> 8) & 0b11111111);
        uniBytes.push_back(decimal & 0b11111111);
    } else if (decimal <= 0x10FFFF) {
        uniBytes.push_back((decimal >> 24) & 0b11111111);
        uniBytes.push_back((decimal >> 16) & 0b11111111);
        uniBytes.push_back((decimal >> 8) & 0b11111111);
        uniBytes.push_back(decimal & 0b11111111);
    }

    while (uniBytes.size() > 1 && uniBytes[0] == 0) {
        uniBytes.erase(uniBytes.begin());
    }

    return uniBytes;
}


vector<unsigned char> decimalToUtf8(int decimal) {
    vector<unsigned char> utf8;

    if (decimal <= 0x7F) {
        utf8.push_back(decimal);
    } else if (decimal <= 0x7FF) {
        utf8.push_back((0b11000000 | (decimal >> 6)));
        utf8.push_back((0b10000000 | (decimal & 0b00111111)));
    } else if (decimal <= 0xFFFF) {
        utf8.push_back((0b11100000 | (decimal >> 12)));
        utf8.push_back((0b10000000 | ((decimal >> 6) & 0b00111111)));
        utf8.push_back((0b10000000 | (decimal & 0b00111111)));
    } else if (decimal <= 0x10FFFF) {
        utf8.push_back((0b11110000 | (decimal >> 18)));
        utf8.push_back((0b10000000 | ((decimal >> 12) & 0b00111111)));
        utf8.push_back((0b10000000 | ((decimal >> 6) & 0b00111111)));
        utf8.push_back((0b10000000 | (decimal & 0b00111111)));
    }

    return utf8;
}