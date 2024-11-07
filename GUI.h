#ifndef GUI_H
#define GUI_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QSpinBox>
#include <iostream>
#include "Student.h"
#include "ISorter.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
#include "ArraySequence.h"
#include "ListSequence.h"


class StudentGUI : public QWidget {
    Q_OBJECT
    signals:
        void dummySignal();
private:
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* idEdit;
    QSpinBox* dobDaySpinBox;
    QSpinBox* dobMonthSpinBox;
    QSpinBox* dobYearSpinBox;
    QSpinBox* yearOfStudySpinBox;
    QPushButton* addStudentButton;
    QListWidget* studentListWidget;

    QComboBox* sorterComboBox;
    QComboBox* comparatorComboBox;
    QComboBox* sequenceComboBox;

    QPushButton* sortButton;
    QListWidget* sortedStudentListWidget;

    ShrdPtr<Sequence<Student>> studentSequence;


public:
    StudentGUI(QWidget* parent = nullptr) : QWidget(parent) {
        // Input fields
        firstNameEdit = new QLineEdit();
        lastNameEdit = new QLineEdit();
        idEdit = new QLineEdit();
        dobDaySpinBox = new QSpinBox();  dobDaySpinBox->setRange(1, 31);
        dobMonthSpinBox = new QSpinBox(); dobMonthSpinBox->setRange(1, 12);
        dobYearSpinBox = new QSpinBox(); dobYearSpinBox->setRange(1900, 2024);
        yearOfStudySpinBox = new QSpinBox(); yearOfStudySpinBox->setRange(1, 6);


        addStudentButton = new QPushButton("Add Student");
        studentListWidget = new QListWidget();

        // Sorting controls
        sorterComboBox = new QComboBox();
        sorterComboBox->addItem("Bubble Sort");
        sorterComboBox->addItem("Heap Sort");
        sorterComboBox->addItem("Insertion Sort");
        sorterComboBox->addItem("Quick Sort");
        sorterComboBox->addItem("Selection Sort");
        sorterComboBox->addItem("Shell Sort");

        comparatorComboBox = new QComboBox();
        comparatorComboBox->addItem("By ID");
        comparatorComboBox->addItem("By Year");
        comparatorComboBox->addItem("By Last Name");
        comparatorComboBox->addItem("By First Name");


        sequenceComboBox = new QComboBox();
        sequenceComboBox->addItem("Array Sequence");
        sequenceComboBox->addItem("List Sequence");
        int initialSequenceType = sequenceComboBox->currentIndex();

        if (initialSequenceType == 0) {
            studentSequence = ShrdPtr<Sequence<Student>>(new ArraySequence<Student>());
        } else {
            studentSequence = ShrdPtr<Sequence<Student>>(new ListSequence<Student>());
        }

        sortButton = new QPushButton("Sort");
        sortedStudentListWidget = new QListWidget();

        // Layout
        QVBoxLayout* mainLayout = new QVBoxLayout();

        // Input Layout
        QGridLayout *inputLayout = new QGridLayout;
        inputLayout->addWidget(new QLabel("First Name:"), 0, 0);
        inputLayout->addWidget(firstNameEdit, 0, 1);
        inputLayout->addWidget(new QLabel("Last Name:"), 1, 0);
        inputLayout->addWidget(lastNameEdit, 1, 1);
        inputLayout->addWidget(new QLabel("ID:"), 2, 0);
        inputLayout->addWidget(idEdit, 2, 1);
        inputLayout->addWidget(new QLabel("Date of Birth:"), 3, 0);

        QHBoxLayout* dobLayout = new QHBoxLayout();
        dobLayout->addWidget(dobDaySpinBox);
        dobLayout->addWidget(dobMonthSpinBox);
        dobLayout->addWidget(dobYearSpinBox);
        inputLayout->addLayout(dobLayout, 3, 1);

        inputLayout->addWidget(new QLabel("Year of Study:"), 4, 0);
        inputLayout->addWidget(yearOfStudySpinBox, 4, 1);
        inputLayout->addWidget(addStudentButton, 5, 0, 1, 2); // span two columns


        mainLayout->addLayout(inputLayout);
        mainLayout->addWidget(studentListWidget);

        //Sorting layout
        QHBoxLayout* sortingLayout = new QHBoxLayout();
        sortingLayout->addWidget(new QLabel("Sorter:"));
        sortingLayout->addWidget(sorterComboBox);
        sortingLayout->addWidget(new QLabel("Comparator:"));
        sortingLayout->addWidget(comparatorComboBox);
        sortingLayout->addWidget(new QLabel("Sequence:"));
        sortingLayout->addWidget(sequenceComboBox);
        mainLayout->addLayout(sortingLayout);




        mainLayout->addWidget(sortButton);
        mainLayout->addWidget(sortedStudentListWidget);

        setLayout(mainLayout);

        connect(addStudentButton, &QPushButton::clicked, this, &StudentGUI::addStudent);
        connect(sortButton, &QPushButton::clicked, this, &StudentGUI::sortStudents);
    }


private slots:

    void addStudent() {
        QString firstName = firstNameEdit->text();
        QString lastName = lastNameEdit->text();

        bool idOk;
        int id = idEdit->text().toInt(&idOk);
        if (!idOk) {
            std::cerr << "Invalid ID input." << std::endl;
            return; // or show an error message to the user
        }
        int dob[3] = {dobDaySpinBox->value(), dobMonthSpinBox->value(), dobYearSpinBox->value()};
        int year = yearOfStudySpinBox->value();

        Student student(firstName.toStdString().c_str(), lastName.toStdString().c_str(), id, dob, year);

        // Clear input fields (optional)
        firstNameEdit->clear();
        lastNameEdit->clear();
        idEdit->clear();

        updateStudentListWidget();


    }

    void sortStudents() {
        // Get sorter
        int sorterIndex = sorterComboBox->currentIndex();
        ISorter<Student, bool(*)(const Student&, const Student&)>* sorter = nullptr;

        switch (sorterIndex) {
        case 0: sorter = new BubbleSort<Student, bool(*)(const Student&, const Student&)>(); break;
        case 1: sorter = new HeapSort<Student, bool(*)(const Student&, const Student&)>(); break;
        case 2: sorter = new InsertionSort<Student, bool(*)(const Student&, const Student&)>(); break;
        case 3: sorter = new QuickSort<Student, bool(*)(const Student&, const Student&)>(); break;
        case 4: sorter = new SelectionSort<Student, bool(*)(const Student&, const Student&)>(); break;
        case 5: sorter = new ShellSort<Student, bool(*)(const Student&, const Student&)>(); break;
        }


        int comparatorIndex = comparatorComboBox->currentIndex();
        auto comparator = [&]() -> bool (*)(const Student&, const Student&) {
            switch (comparatorComboBox->currentIndex()) {
                case 0: return [](const Student& s1, const Student& s2) { return CompareStudentsByID()(s1, s2); };
                case 1: return [](const Student& s1, const Student& s2) { return CompareStudentsByYear()(s1, s2); };
                case 2: return [](const Student& s1, const Student& s2) { return CompareStudentsByLastName()(s1, s2); };
                case 3: return [](const Student& s1, const Student& s2) { return CompareStudentsByFirstName()(s1, s2); };
                default: return nullptr; // Или бросить исключение
            }
        }();

        if (sorter && comparator && studentSequence && studentSequence->GetLength() > 0) {
            ShrdPtr<Sequence<Student>> sortedSequence = studentSequence->Copy();
            sorter->Sort(sortedSequence, comparator);


            sortedStudentListWidget->clear();
            for (int i = 0; i < sortedSequence->GetLength(); ++i) {
                sortedStudentListWidget->addItem(QString::fromStdString(std::string(sortedSequence->Get(i).getFirstName()) + " " + sortedSequence->Get(i).getLastName() + ", ID: " + std::to_string(sortedSequence->Get(i).getID())));
            }
        }

        delete sorter;

    }



    void updateStudentListWidget() {
        studentListWidget->clear();
        for (int i = 0; i < studentSequence->GetLength(); ++i) {
            studentListWidget->addItem(QString::fromStdString(std::string(studentSequence->Get(i).getFirstName()) + " " + studentSequence->Get(i).getLastName() + ", ID: " + std::to_string(studentSequence->Get(i).getID())));
        }
    }

};

#endif