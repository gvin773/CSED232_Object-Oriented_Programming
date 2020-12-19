#include "timetablewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimetableWindow w;
    w.show();
    return a.exec();
}
