#include "Tests.h"
#include "GUI.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    StudentGUI gui;
    gui.setWindowTitle("Student Sorting");
    gui.show();


    return app.exec();
}