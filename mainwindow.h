#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class PlotWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PlotWindow *mpPlot;
    QString mBinDir;
    QString mBinFile;
    bool check() const;
    void displayPlot(QVector<double> &,QVector<double> &);

private slots:
    void start();
    void selectBin();

};
#endif // MAINWINDOW_H
