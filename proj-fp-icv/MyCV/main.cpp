#include "mainwindow.h"

#include <QApplication>

/*
    Main function -> creates MainWindow object
    Used icons are Creative Commons 0, or made by me.
    Program written by Eric Wolf for the CS50 course.
*/

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();

}
