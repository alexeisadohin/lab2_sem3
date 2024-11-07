#include "Student.h"
#include <cstring>
#include <limits>
#include <iomanip>
#include <iostream>

Person::Person() : firstName(nullptr), lastName(nullptr), ID(0) {
    dateOfBirth[0] = dateOfBirth[1] = dateOfBirth[2] = 0;
}

Person::Person(const char* firstName, const char* lastName, int ID, const int dob[3]) : ID(ID) {
    this->firstName = new char[std::strlen(firstName) + 1];
    std::strcpy(this->firstName, firstName);
    this->lastName = new char[std::strlen(lastName) + 1];
    std::strcpy(this->lastName, lastName);
    std::copy(dob, dob + 3, this->dateOfBirth);
}

Person::~Person() {
    delete[] firstName;
    delete[] lastName;
}

Person::Person(const Person& other) : ID(other.ID) {
    firstName = new char[std::strlen(other.firstName) + 1];
    std::strcpy(firstName, other.firstName);
    lastName = new char[std::strlen(other.lastName) + 1];
    std::strcpy(lastName, other.lastName);
    std::copy(other.dateOfBirth, other.dateOfBirth + 3, dateOfBirth);
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        char* newFirstName = new char[std::strlen(other.firstName) + 1];
        char* newLastName = new char[std::strlen(other.lastName) + 1];
        std::strcpy(newFirstName, other.firstName);
        std::strcpy(newLastName, other.lastName);

        delete[] firstName;
        delete[] lastName;

        firstName = newFirstName;
        lastName = newLastName;
        ID = other.ID;
        std::copy(other.dateOfBirth, other.dateOfBirth + 3, dateOfBirth);
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Person& person) {
    char buffer[256];
    std::cout << "Enter first name: ";
    is >> std::setw(256) >> buffer;
    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (!std::isalpha(buffer[i])) {
            std::cout << "Invalid input. Please enter a valid name: ";
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            is >> std::setw(256) >> buffer;
            i = -1;
        }
    }
    delete[] person.firstName;
    person.firstName = new char[std::strlen(buffer) + 1];
    std::strcpy(person.firstName, buffer);

    std::cout << "Enter last name: ";
    is >> std::setw(256) >> buffer;
    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (!std::isalpha(buffer[i])) {
            std::cout << "Invalid input. Please enter a valid name: ";
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            is >> std::setw(256) >> buffer;
            i = -1;
        }
    }
    delete[] person.lastName;
    person.lastName = new char[std::strlen(buffer) + 1];
    std::strcpy(person.lastName, buffer);

    std::cout << "Enter ID: ";
    while (!(is >> person.ID)) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number for ID: ";
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter date of birth (day month year): ";
    for (int& dob : person.dateOfBirth) {
        while (!(is >> dob)) {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number for date of birth: ";
        }
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return is;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Name: " << person.firstName << " " << person.lastName
       << ", ID: " << person.ID
       << ", Date of Birth: " << person.dateOfBirth[0] << "/"
       << person.dateOfBirth[1] << "/" << person.dateOfBirth[2];
    return os;
}

Student::Student() : Person(), yearOfStudy(0) {}

Student::Student(const char* firstName, const char* lastName, int ID, const int dob[], int year)
    : Person(firstName, lastName, ID, dob), yearOfStudy(year) {}

Student::Student(const Student& other) : Person(other), yearOfStudy(other.yearOfStudy) {}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Person::operator=(other);
        yearOfStudy = other.yearOfStudy;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Student& student) {
    is >> static_cast<Person&>(student);
    std::cout << "Enter year of study: ";
    while (!(is >> student.yearOfStudy)) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number for year of study: ";
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << static_cast<const Person&>(student)
       << ", Year of Study: " << student.yearOfStudy;
    return os;
}

