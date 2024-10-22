#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

bool PlotWindow::displayGraph(QVector<double> & x,QVector<double> &y)
{
    int xSize = x.size();
    int ySize = y.size();
    if(xSize < 1 || ySize < 1)
        return false;


    ui->plot->addGraph();
    ui->plot->graph(ui->plot->graphCount()-1)->setData(x, y);

    ui->plot->xAxis->setLabel("N");
    ui->plot->yAxis->setLabel("TIME");

    // set ranges
    // double xLower = std::min(plot->xAxis->range().lower, 0);
    double xUpper = std::max(ui->plot->xAxis->range().upper, x[xSize-1]);

    // double yLower = std::min(plot->yAxis->range().lower, 0);
    double yUpper = std::max(ui->plot->yAxis->range().upper, y[ySize-1]);

    ui->plot->xAxis->setRange(0, xUpper);
    ui->plot->yAxis->setRange(0, yUpper);

    ui->plot->replot();
    return true;
}
