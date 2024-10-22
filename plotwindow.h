#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();
    bool displayGraph(QVector<double> & x,QVector<double> &y);

private:
    Ui::PlotWindow *ui;

};

#endif // PLOTWINDOW_H
