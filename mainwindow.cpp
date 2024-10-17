#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QStringListModel>
#include <QListView>
#include <QStringList>
#include <QElapsedTimer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mBinDir {"/home/ali/qt_projects/ComplexityTest/bin"}
{
    ui->setupUi(this);
    // connect exit button
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
    // connect run button
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::start);
    // connect select button
    connect(ui->selectBinButton, &QPushButton::clicked, this, &MainWindow::selectBin);

    // setup validators
    auto fromToVal = new QIntValidator(0,10000000);
    ui->fromLineEdit->setValidator(fromToVal);
    ui->toLineEdit->setValidator(fromToVal);

    auto stepVal = new QIntValidator(1,1000000);
    ui->stepLineEdit->setValidator(stepVal);

    // setup selectBin line edit
    ui->selectBinLineEdit->setText(mBinFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check() const
{
    // check weather a file is selected
    if(ui->selectBinLineEdit->text() == "")
        return false;

    // check the range
    int from = ui->fromLineEdit->text().toInt();
    int to = ui->toLineEdit->text().toInt();
    int step = ui->stepLineEdit->text().toInt();

    if(from < 0 || to < 0 || step < 0) // 0 means conversion failed
        return false;
    if(from > to)
        return false;

    return true;
}

QString run(QString binFile, int n) // binFile should be absolute path of the bin file
{
    QProcess p;
    QString command = "/bin/bash -c "
                      + QString(" \"")
                      + binFile + " "
                      + QString::number(n)
                      + " \"";
    QElapsedTimer timer;
    timer.start();

    p.startCommand(command);
    p.waitForFinished();

    qint64 time { timer.elapsed() };

    QString elapsedTime = "for n=" + QString::number(n) + ":\t "  + QString::number(time) + " ms";
    return elapsedTime;
}

void MainWindow::selectBin()
{
    QString binFile = QFileDialog::getOpenFileName(this,
                                                   "Select binary file",
                                                   mBinDir,
                                                   "");
    if(binFile != "")
    {
        ui->selectBinLineEdit->setText(binFile);
        mBinFile = binFile;
    }
}

void MainWindow::start()
{

    if(check())
    {
        // QString list for QStringListModel
        QStringList outputList; // managed by the mainwindow
        // get range
        int from = ui->fromLineEdit->text().toInt();
        int to = ui->toLineEdit->text().toInt();
        int step = ui->stepLineEdit->text().toInt();

        while(from <= to)
        {
            outputList <<  run(mBinFile,from);
            from += step;
        }

        // the QStringListModel
        auto model = new QStringListModel(outputList);

        auto v = new QListView();
        v->setModel(model);
        v->show();
    }
}

