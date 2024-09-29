#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QStringListModel>
#include <QListView>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect exit button
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
    // connect run button
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::start);

    // setup validators
    auto fromToVal = new QIntValidator(0,10000000);
    ui->fromLineEdit->setValidator(fromToVal);
    ui->toLineEdit->setValidator(fromToVal);

    auto stepVal = new QIntValidator(1,1000000);
    ui->stepLineEdit->setValidator(stepVal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkRange() const
{
    // get the range
    int from = ui->fromLineEdit->text().toInt();
    int to = ui->toLineEdit->text().toInt();
    int step = ui->stepLineEdit->text().toInt();

    if(from < 0 || to < 0 || step < 0) // 0 means conversion failed
        return false;
    if(from > to)
        return false;

    return true;
}

QString run(int n)
{
    QProcess p;
    QString command = "/usr/bin/time -f \"%e elapsed\" "
                      "/home/ali/qt_projects/ComplexityTest/algo_main " + QString::number(n);
    p.startCommand(command);
    p.waitForFinished();

    QString stdout = p.readAllStandardOutput();
    qDebug() << stdout;

    QString elapsedTime = "for n=" + QString::number(n) + ":\t "  + p.readAllStandardError();
    return elapsedTime;
}

void MainWindow::start()
{
    if(checkRange())
    {
        // QString list for QStringListModel
        QStringList outputList; // managed by the mainwindow
        // get range
        int from = ui->fromLineEdit->text().toInt();
        int to = ui->toLineEdit->text().toInt();
        int step = ui->stepLineEdit->text().toInt();

        while(from < to)
        {
            outputList <<  run(from);
            from += step;
        }

        // the QStringListModel
        auto model = new QStringListModel(outputList);

        auto v = new QListView();
        v->setModel(model);
        v->show();
    }
}

