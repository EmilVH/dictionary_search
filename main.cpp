#include <QApplication>
#include <QPushButton>
#include "QtWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow window1;
    window1.show();
    return QApplication::exec();
}
