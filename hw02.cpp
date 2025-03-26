// Anemka Lydia Legbara
// Hw02
// Warrior game for medieval times
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>

using namespace std;

struct Warrior {
    string name;
    int strength;

};

// prints the amount of warriors and the warrior's names and strength
void printStatus(const vector<Warrior>& warriors);

// finds the index of the warriors
size_t findWarrior(const vector<Warrior>& warriors, const string& warriorName);

// prints out the results of the battles and changes strength based on battle results
void battle(Warrior& warrior1, Warrior& warrior2);

// reads file and figures out what the instructions for the warriors
int main() {
    ifstream file("warriors.txt");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    vector<Warrior> warriors;
    string instructions;

    while (file >> instructions) {
        if (instructions == "Warrior") {
            string name;
            int strength;
            file >> name >> strength;
            warriors.push_back(Warrior{name, strength});
        } else if (instructions == "Battle") {
            string name1, name2;
            file >> name1 >> name2;

            int index1 = findWarrior(warriors, name1);
            int index2 = findWarrior(warriors, name2);

            if (index1 != -1 && index2 != -1) {
                battle(warriors[index1], warriors[index2]);
            }
        } else if (instructions == "Status") {
            printStatus(warriors);
        }
    }

    file.close();
    return 0;
}

void printStatus(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << "Warrior: " << warrior.name << ", strength: " << warrior. strength << endl;
    }
}

size_t findWarrior(const vector<Warrior>& warriors, const string& warriorName) {
    for (int index = 0; index < warriors.size(); index++) {
        if (warriors[index].name == warriorName) {
            return index;
        }
    }
    return -1;
}

void battle(Warrior& warrior1, Warrior& warrior2) {
    cout << warrior1.name << " battles " << warrior2.name << endl;
    if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.name << endl;
    } else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.name << endl;
    } else if (warrior1.strength > warrior2.strength) {
        warrior1.strength -= warrior2.strength;
        warrior2.strength = 0;
        cout << warrior1.name << " defeats " << warrior2.name << endl;
    } else if (warrior1.strength < warrior2.strength) {
        warrior2.strength -= warrior1.strength;
        warrior1.strength = 0;
        cout << warrior2.name << " defeats " << warrior1.name << endl;
    } else {
        warrior1.strength = 0;
        warrior2.strength = 0;
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name
             << " die at each other's hands" << endl;
    }
}