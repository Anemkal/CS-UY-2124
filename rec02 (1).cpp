// Anemka Lydia Legbara
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct Hydrocarbon {
    vector<string> names;
    int carbon;
    int hydrogen;

};

void openFile(ifstream &file);

size_t findHydrocarbon(const vector<Hydrocarbon> &hydrocarbons, int carbon, int hydrogen);

void insertHydrocarbon(vector<Hydrocarbon> &hydrocarbons, const string &name, int carbon, int hydrogen);

void fillVector(vector<Hydrocarbon> &hydrocarbons, ifstream &file);

void printHydrocarbon(const Hydrocarbon &hydrocarbon);

void displayVector(const vector<Hydrocarbon> &hydrocarbons, const string &title);

void sortVector(vector<Hydrocarbon> &hydrocarbons);

int main() {
    ifstream file;
    vector<Hydrocarbon> hydrocarbons;

    openFile(file);
    fillVector(hydrocarbons, file);
    file.close();

    displayVector(hydrocarbons, "\nUnsorted:");
    sortVector(hydrocarbons);
    displayVector(hydrocarbons, "\nSorted:");

    return 0;
}

void openFile(ifstream &file) {
    string filename;
    while (true) {
        cout << "Enter the filename: ";
        cin >> filename;
        file.open(filename);
        if (file.is_open()) {
            break;
        }
        cout << "Error: Could not open file.\n";
    }
}

size_t findHydrocarbon(const vector<Hydrocarbon> &hydrocarbons, int carbon, int hydrogen) {
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        if (hydrocarbons[i].carbon == carbon && hydrocarbons[i].hydrogen == hydrogen) {
            return i;
        }
    }
    return hydrocarbons.size();
}

void insertHydrocarbon(vector<Hydrocarbon> &hydrocarbons, const string &name, int carbon, int hydrogen) {
    size_t index = findHydrocarbon(hydrocarbons, carbon, hydrogen);
    if (index == hydrocarbons.size()) {
        Hydrocarbon newHydrocarbon;
        newHydrocarbon.names.push_back(name);
        newHydrocarbon.carbon = carbon;
        newHydrocarbon.hydrogen = hydrogen;
        hydrocarbons.push_back(newHydrocarbon);
    } else {
        hydrocarbons[index].names.push_back(name);
    }
}

void fillVector(vector<Hydrocarbon> &hydrocarbons, ifstream &file) {
    string name;
    char c, h;
    int carbon, hydrogen;

    while (file >> name >> c >> carbon >> h >> hydrogen) {
        if (c == 'C' && h == 'H') {
            insertHydrocarbon(hydrocarbons, name, carbon, hydrogen);
        }
    }
}

void printHydrocarbon(const Hydrocarbon &hydrocarbon) {
    cout << "C" << hydrocarbon.carbon << "H" << hydrocarbon.hydrogen;
    for (size_t i = 0; i < hydrocarbon.names.size(); i++) {
        cout << " " << hydrocarbon.names[i];
    }
    cout << endl;
}

void displayVector(const vector<Hydrocarbon> &hydrocarbons, const string &title) {
    cout << title << endl;
    for (size_t i = 0; i < hydrocarbons.size(); i++) {
        printHydrocarbon(hydrocarbons[i]);
    }
}

void sortVector(vector<Hydrocarbon> &hydrocarbons) {
    size_t n = hydrocarbons.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (hydrocarbons[j].carbon > hydrocarbons[j + 1].carbon ||
               (hydrocarbons[j].carbon == hydrocarbons[j + 1].carbon &&
                hydrocarbons[j].hydrogen > hydrocarbons[j + 1].hydrogen)) {
                swap(hydrocarbons[j], hydrocarbons[j + 1]);
                }
        }
    }
}