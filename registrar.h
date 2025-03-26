#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <vector>
#include <string>
#include "course.h"
#include "student.h"
namespace BrooklynPoly {
    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        bool addCourse(const std::string& courseName);
        bool addStudent(const std::string& studentName);
        bool enrollStudentInCourse(const std::string& studentName, const std::string& courseName);
        bool cancelCourse(const std::string& courseName);
        void purge();

    private:
        size_t findStudent(const std::string& studentName) const;
        size_t findCourse(const std::string& courseName) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}
#endif

