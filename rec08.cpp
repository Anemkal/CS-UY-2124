#include <iostream>
#include <string>
#include <vector>
#include "registrar.h"


using namespace std;
using namespace BrooklynPoly;

int main() {
    Registrar registrar;

    cout << "Adding courses and students...\n";
    registrar.addCourse("CS101.001");
    registrar.addStudent("FritzTheCat");
    registrar.addCourse("CS102.001");

    cout << "Enrolling students...\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");

    cout << registrar << endl;

    cout << "Canceling a course...\n";
    registrar.cancelCourse("CS102.001");

    cout << registrar << endl;

    cout << "Purging all data...\n";
    registrar.purge();

    cout << registrar << endl;

    return 0;
}