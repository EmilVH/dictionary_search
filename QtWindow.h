

#ifndef ECHODIALOG_H
#define ECHODIALOG_H

#include <QWidget>
#include <QTextEdit>
#include <QTimer>
#include <QMainWindow>

#include "QtInterface.h"
#include "Finder.h"

QT_BEGIN_NAMESPACE
class QString;

class QLineEdit;

class QLabel;

class QPushButton;

class QGridLayout;

QT_END_NAMESPACE


class EchoWindow : public QWidget {
Q_OBJECT

public:
    EchoWindow();

private slots:

    void sendEcho();

private:
    void createGUI();

    Finder finder_;
    bool closed = true;
    QLineEdit *input_field_;
    QTextEdit *output_field_;
    QPushButton *button_;
    QGridLayout *layout_;
    std::thread generator;
    QTimer *updater_;

    void start_generating();
};

class MainWindow : public QMainWindow {
public:
    MainWindow();

    EchoWindow window;
};

#endif //PREPROCESSOR_QTWINDOW_H
