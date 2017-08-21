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
    QString str;
    doMessage(str=doSelectingBmp(true));

    QGraphicsScene *scena = new QGraphicsScene(ui->graphicsView);
    QPixmap mapPxs(str);
    QGraphicsView *view = ui->graphicsView;
    view->setFixedHeight(mapPxs.height());
    view->setFixedWidth(mapPxs.width());
    scena->addPixmap(mapPxs);
    view->setScene(scena);
    view->fitInView(scena->itemsBoundingRect(),Qt::KeepAspectRatio);
    view->show();
}

void MainWindow::on_actionExport_triggered()
{
    doMessage(doSelectingBmp(false));
}

void MainWindow::on_pushButton_clicked()
{

}
