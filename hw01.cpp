// Anemka Lydia Legbara
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

char decrypt(char c, size_t rotation) {
    if (c>='A' && c<='Z') {
        c -= rotation;
        if (c < 'A') {
            c += 26;
        }
    }
    return c;
}
int main() {
    ifstream input_File("encrypted.txt");
    if (!input_File.is_open()) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    string line;
    size_t rotation;
    input_File >> rotation;

    vector<string> contents;
    while (getline(input_File, line)) {
        contents.push_back(line);
    }

    input_File.close();

    for (size_t idx = contents.size() - 1; idx >= 0; --idx) {
        string decrypted_line;
        for (char c : contents[idx]) {
            decrypted_line += decrypt(c, rotation);
        }
        cout << decrypted_line << endl;
    }
    return 0;
}