#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include <algorithm>
class Person {
private:
    char* firstName;
    char* lastName;
    int ID;
    int dateOfBirth[3];
public:
    Person();
    Person(const char* firstName, const char* lastName, int ID, const int dob[3]);
    virtual ~Person();

    Person(const Person& other);
    Person& operator=(const Person& other);

    const char* getFirstName() const { return firstName; }
    const char* getLastName() const { return lastName; }
    int getID() const { return ID; }
    const int* getDateOfBirth() const { return dateOfBirth; }

    friend std::istream& operator>>(std::istream& is, Person& person);
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

class Student : public Person {
private:
    int yearOfStudy;
public:
    Student();
    Student(const char* firstName, const char* lastName, int ID, const int dob[], int year);

    Student(const Student& other);
    Student& operator=(const Student& other);
    int getYearOfStudy() const {return yearOfStudy; }

    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

struct CompareStudentsByID {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getID() < s2.getID();
    }
};

struct CompareStudentsByYear {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getYearOfStudy() < s2.getYearOfStudy();
    }
};


struct CompareStudentsByLastName {
    bool operator()(const Student& s1, const Student& s2) const {
        std::string lastName1 = s1.getLastName();  // Assuming you have getLastName()
        std::string lastName2 = s2.getLastName();
        return lastName1 < lastName2; // Case-sensitive comparison
    }
};

// Comparator for sorting by first name (case-insensitive)
struct CompareStudentsByFirstName {
    bool operator()(const Student& s1, const Student& s2) const {
        std::string firstName1 = s1.getFirstName(); // Assuming you have getFirstName()
        std::string firstName2 = s2.getFirstName();

        // Convert to lowercase for case-insensitvie comparison:
        std::transform(firstName1.begin(), firstName1.end(), firstName1.begin(), ::tolower);
        std::transform(firstName2.begin(), firstName2.end(), firstName2.begin(), ::tolower);

        return firstName1 < firstName2;
    }
};

#endif //STUDENT_H
