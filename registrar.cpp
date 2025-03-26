#include "registrar.h"
#include <iostream>
#include <string>
using namespace std;
namespace BrooklynPoly {
    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) == students.size()) {
            students.push_back(new Student(studentName));
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);
        if (studentIndex < students.size() && courseIndex < students.size()) {
            return courses[courseIndex]->addStudent(students[studentIndex]) &&
                students[studentIndex]->addCourse(courses[courseIndex]);
        }
        return false;
    }

    bool Registrar::cancelCourse(const string& courseName) {
        size_t removal = 0;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i] -> getName() == courseName) {
                courses[i]-> removeStudentsFromCourse();
                removal = i;
                break;
            }
        }
        delete courses[removal];
        for (size_t i = removal; i < courses.size()-1; i++) {
            courses[i] = courses[i+1];
        }
        courses.pop_back();
        return true;

    }

    void Registrar::purge() {
        for (Course* course : courses) {
            delete course;
        }
        for (Student* student : students) {
            delete student;
        }
        courses.clear();
        students.clear();
    }

    size_t Registrar::findStudent(const std::string& studentName) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i]->getName() == studentName) {
                return i;
            }
        }
        return students.size();
    }

    bool Registrar::addCourse(const string& courseName) {
        if (findCourse(courseName) == courses.size()) {
            courses.push_back(new Course(courseName));
            return true;
        }
        return false;
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]-> getName() == courseName) {
                return i;
            }
        }
        return courses.size();
    }

    ostream& operator<<(ostream& os, const Registrar& rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (size_t i = 0; i < rhs.courses.size(); i++) {
            os << *(rhs.courses[i]);
        }
        os << "Students: " << endl;
        for (size_t i = 0; i < rhs.students.size(); i++) {
            os << *(rhs.students[i]);
        }
        return os;
    }
}