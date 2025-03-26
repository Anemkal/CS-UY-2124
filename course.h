#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
namespace BrooklynPoly {
    class Student;  // Forward declaration to avoid cyclic dependency

    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* student);
        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    };
}
#endif

