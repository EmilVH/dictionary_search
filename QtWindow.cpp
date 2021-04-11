#include "QtWindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPluginLoader>
#include <QPushButton>
#include <string>
#include <QScreen>

EchoWindow::EchoWindow() : finder_("prepared.txt") {
    createGUI();
    setLayout(layout_);
    setWindowTitle("Dictionary finder");
}

void EchoWindow::sendEcho() {
    std::string pattern = input_field_->text().toStdString();
    if (!closed) {
        closed = true;
        finder_.stop_finding();
    }
    closed = false;
    finder_.insert_new_pattern(pattern);
    output_field_->setText("");
    updater_ = new QTimer(this);
    updater_->setInterval(100);
    updater_->setSingleShot(false);
    connect(updater_, &QTimer::timeout, this, &EchoWindow::start_generating);
    updater_->start();
    start_generating();
}

void EchoWindow::start_generating() {
    int generated = 0;
    while (true) {
        auto res = finder_.get_next();
        generated++;
        if (generated > 1000) {
            break;
        }
        if (res != nullptr) {
            output_field_->append(QString::fromStdString(*res));
        } else {
            break;
        }
    }
}

void EchoWindow::createGUI() {
    resize(1080, 1920);
    input_field_ = new QLineEdit;
    input_field_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    input_field_->setMinimumHeight(50);
    input_field_->setMinimumWidth(400);
    output_field_ = new QTextEdit;
    output_field_->resize(400, 200);
    connect(input_field_, &QLineEdit::textChanged, this, &EchoWindow::sendEcho);
    output_field_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout_ = new QGridLayout;
    output_field_->setReadOnly(true);
    output_field_->setAcceptRichText(true);
    layout_->addWidget(new QLabel(tr("Find:")), 0, 0);
    layout_->addWidget(input_field_, 0, 1);
    layout_->addWidget(new QLabel(tr("Words:")), 1, 0);
    layout_->addWidget(output_field_, 1, 1);
    layout_->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::MainWindow() {
    window.showMaximized();
    setCentralWidget(&window);
}
