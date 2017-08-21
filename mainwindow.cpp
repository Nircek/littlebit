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
void MainWindow::doMessage(QString str){
    QMessageBox qmb(this);
    qmb.setText(str);
    qmb.exec();
}
QString MainWindow::doSelectingBmp(bool mustExist){
    QFileDialog qfd(this);
    qfd.setNameFilter(tr("Bitmap (*.bmp)"));
    qfd.setAcceptMode(mustExist?QFileDialog::AcceptOpen:QFileDialog::AcceptSave);
    if(qfd.exec())return qfd.selectedFiles().at(0);
    else return NULL;

}

void MainWindow::on_actionImport_triggered()
{
    doMessage(doSelectingBmp(true));
}

void MainWindow::on_actionExport_triggered()
{
    doMessage(doSelectingBmp(false));
}
