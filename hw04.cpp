// Anemka Lydia Legbara
// hw04
// Warrior battle simulation with nobles
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& awarrior);
public:
    // Constructor
    Warrior(const string& aName, int aStrength) : name(aName), strength(aStrength), hired(false) {}

    // Getter for the warrior's name
    const string& getName() const { return name; }

    // Getter for strength of warrior
    int getStrength() const { return strength; }

    // Setter for the strength of warrior
    void setStrength(int aStrength) { strength = aStrength; }

    // Checks if the warrior has been hired
    bool isHired() const { return hired; }

    // Updates the hired status
    void updateHired() { hired = !hired; }

private:
    string name;
    int strength;
    bool hired;
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& aNoble);
public:
    // Constructor: Initializes a noble with a name
    Noble(const string& aName) : name(aName), alive(true) {}

    // Attempts to hire a warrior; returns true if successful, false otherwise
    bool hire(Warrior& aWarrior) {
        if (aWarrior.isHired() || !alive) {
            cout << name << " failed to hire " << aWarrior.getName() << endl;
            return false;
        }
        aWarrior.updateHired();
        army.push_back(&aWarrior);
        return true;
    }

    // Attempts to fire a warrior; returns true if successful, false otherwise
    bool fire(Warrior& aWarrior) {
        if (!alive) {
            return false;
        }
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i] == &aWarrior) {
                cout << aWarrior.getName() << ", you don't work for me any more! -- " << name << "." << endl;
                aWarrior.updateHired();
                // Erase element without using .begin()
                for (size_t j = i; j < army.size() - 1; j++) {
                    army[j] = army[j + 1];
                }
                army.pop_back();
                return true;
            }
        }
        cout << name << " failed to fire " << aWarrior.getName() << endl;
        return false;
    }

    // Shows the battles between the nobles
    void battle(Noble& enemy) {
        cout << name << " battles " << enemy.name << endl;

        if (!alive) {
            if (!enemy.alive) {
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            } else {
                cout << "He's dead, " << enemy.name << endl;
            }
            return;
        }
        if (!enemy.alive) {
            cout << "He's dead, " << name << endl;
            return;
        }

        int selfStrength = getArmyStrength();
        int enemyStrength = enemy.getArmyStrength();

        if (selfStrength == enemyStrength) {
            cout << "Mutual Annihilation: " << name << " and " << enemy.name << " die at each other's hands" << endl;
            setArmyStrength(0);
            enemy.setArmyStrength(0);
            alive = false;
            enemy.alive = false;
        } else {
            if (selfStrength > enemyStrength) {
                cout << name << " defeats " << enemy.name << endl;
                updateArmyStrength(1 - (double)enemyStrength / selfStrength);
                enemy.setArmyStrength(0);
                enemy.alive = false;
            } else {
                cout << enemy.name << " defeats " << name << endl;
                enemy.updateArmyStrength(1 - (double)selfStrength / enemyStrength);
                setArmyStrength(0);
                alive = false;
            }
        }
    }

private:
    string name;
    vector<Warrior*> army;
    bool alive;

    // the total strength of the army
    int getArmyStrength() const {
        int totalStrength = 0;
        for (size_t i = 0; i < army.size(); i++) {
            totalStrength += army[i]->getStrength();
        }
        return totalStrength;
    }

    // Sets the strength of warriors in the army
    void setArmyStrength(int value) {
        for (size_t i = 0; i < army.size(); i++) {
            army[i]->setStrength(value);
        }
    }

    // Reduces the warriors' strength by the ratio
    void updateArmyStrength(double ratio) {
        for (size_t i = 0; i < army.size(); i++) {
            army[i]->setStrength(army[i]->getStrength() * ratio);
        }
    }
};

// Operator to print Warrior info
ostream& operator<<(ostream& os, const Warrior& awarrior) {
    os << "\t" << awarrior.name << ": " << awarrior.strength;
    return os;
}

// Operator to print Noble andf army info
ostream& operator<<(ostream& os, const Noble& aNoble) {
    os << aNoble.name;
    if (!aNoble.alive) {
        os << " is dead";
    } else {
        os << " has an army of " << aNoble.army.size();
        for (size_t i = 0; i < aNoble.army.size(); i++) {
            os << endl << *(aNoble.army[i]);
        }
    }
    return os;
}

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    return 0;
}

