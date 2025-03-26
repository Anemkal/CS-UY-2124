// Anemka Lydia Legbara
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {

    friend ostream& operator<<(ostream& os, const Section& section) {
        os << "Section: " << section.sectionName << ", " << section.time << endl;
        if (section.students.size() == 0) {
            os << "None" << endl;
        } else {
            os << endl;
            for (size_t i = 0; i < section.students.size(); i++) {
                os << "Name: " << *section.students[i] << endl;
            }
        }
        return os;
    }
    class StudentRecord {
        string name;
        vector<int> grades;
    public:
        const string& getName() const {
            return name;
        }

        StudentRecord(const string& studentName) : name(studentName), grades(14, -1) {}
        friend ostream& operator<<(ostream& os, const StudentRecord& record) {
            os << record.name << " Grades: ";
            for (int grade : record.grades) {
                os << grade << " ";
            }
            return os;
        }

        void setGrade(int grade, int week) {
            if (week >= 1 && week <= 14) {
                grades[week - 1] = grade;
            }
        }
    };
    class TimeSlot {
        string day;
        int hour;
    public:
        TimeSlot(const string& theDay, int theHour) : day(theDay), hour(theHour) {}
        friend ostream& operator<<(ostream& os, const TimeSlot& slot) {
            os << "Time slot: [ Day:" << slot.day << ", Start time: ";
            int time = slot.hour;
            if (slot.hour < 12) {
                os << slot.hour << "am]";
            } else {
                time-=12;
                os << time << "pm]";
            }
return os;
        }
    };
    string sectionName;
    TimeSlot time;
    vector<StudentRecord*> students;
public:
    Section(const string& name, const string& day, int hour) : sectionName(name), time(day, hour) {}

    void addStudent(const string& studentName) {
        students.push_back(new StudentRecord(studentName));
    }

    Section(const Section& copySection) : sectionName(copySection.sectionName), time(copySection.time) {
        for (size_t i = 0; i < copySection.students.size(); i++) {
            StudentRecord* copy = new StudentRecord(*copySection.students[i]);
            students.push_back(copy);
        }
    }
        ~Section() {
        cout << "Section: " << sectionName << " is being deleted " << endl;
        for (StudentRecord* student : students) {
            cout << "Deleting " << student->getName() << endl;
            delete student;
        }
        students.clear();
    }
    /*
    operator=(const Section& section) {
        for (StudentRecord* student : students) {
            cout << "Deleting " << student->getName() << endl;
            delete student;
        }
        students.clear();
        sectionName = section.sectionName;
        for (size_t i = 0; i < copySection.students.size(); i++) {
            StudentRecord* copy = new StudentRecord(*copySection.students[i]);
            students.push_back(copy);
        }
    }
    */
    void addGrade(const string& name, int grade, int week) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i] -> getName() == name) {
                students[i]-> setGrade(grade, week);
            }
        }
    }
};


    class LabWorker {
        string name;
        Section* section;
    public:
        LabWorker(const string& name) : name(name), section(nullptr) {}

        void addSection(Section& sec) {
            section = &sec;
        }

        void addGrade(const string& name, int grade, int week) {
            if (section != nullptr) {
                section->addGrade(name, grade, week);
            }
        }

        friend ostream& operator<<(ostream& os, const LabWorker& worker) {
            os << worker.name;
            if (worker.section) {
                os << " has section: " << *worker.section;
            } else {
                os << "has no section assigned";
            }
            return os;
        }
    };

// Test code
void doNothing(Section sec) {cout << sec << endl;}

int main() {
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

}
    // main
