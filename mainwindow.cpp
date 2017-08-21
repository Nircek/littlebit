#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImport_triggered()
{
    QString fileName;
    QFileDialog qfd(this);
    qfd.setNameFilter(tr("Bitmap (*.bmp)"));
    if(qfd.exec()){
        fileName=qfd.selectedFiles().at(0);
        QMessageBox qmb(this);
        qmb.setText(fileName);
        qmb.exec();
    }
}
