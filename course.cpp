#include "course.h"
#include "student.h"
#include <iostream>
using namespace std;
namespace BrooklynPoly {
    Course::Course(const std::string& courseName) : name(courseName) {}

    const std::string& Course::getName() const {
        return name;
    }

    bool Course::addStudent(Student* student) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i] == student) {
                return false;
            }
        }
        students.push_back(student);
        return true;
    }

    void Course::removeStudentsFromCourse() {
        for (Student * student : students) {
            student->removedFromCourse(this);
        }
        students.clear();
    }

    ostream& operator<<(ostream& os, const Course& rhs) {
        os << rhs.name << ": ";
        if (rhs.students.size() == 0) {
            os << "No Students" << endl;
        } else {
            for (size_t i = 0; i < rhs.students.size(); i++) {
                os << rhs.students[i]->getName() << endl;
            }
        }
        return os;
    }
}