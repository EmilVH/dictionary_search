#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include "QtWindow.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    /*QPushButton button("Helo world!", nullptr);
    QPushButton button2("Popa world!", nullptr);
    button.resize(200, 100);
    button2.resize(200, 100);
    button.show();
    button2.show();*/
    MainWindow window1;
    window1.show();

    return QApplication::exec();
}
