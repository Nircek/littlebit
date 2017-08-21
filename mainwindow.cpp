#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>

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
    doMessage(imgstr=doSelectingBmp(true));

    scena = new QGraphicsScene(ui->graphicsView);
    mapPxs = new QPixmap(imgstr);
    view = ui->graphicsView;
    view->setFixedHeight(mapPxs->height());
    view->setFixedWidth(mapPxs->width());
    scena->addPixmap(*mapPxs);
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
    QImage img = mapPxs->toImage();
    int shift=ui->spinBox->value();
    for(int w=0;w<img.width();++w){
        for(int h=0;h<img.height();++h){
            QColor prev=img.pixel(w,h);
            int r=((prev.red()>>shift)|(prev.red()<<(8-shift)))%256;
            int g=((prev.green()>>shift)|(prev.green()<<(8-shift)))%256;
            int b=((prev.blue()>>shift)|(prev.blue()<<(8-shift)))%256;
            img.setPixelColor(w,h,QColor(r,g,b));
        }
    }
    mapPxs = new QPixmap(QPixmap::fromImage(img));
    scena = new QGraphicsScene(ui->graphicsView);
    scena->addPixmap(*mapPxs);
    view->setScene(scena);
    view->fitInView(scena->itemsBoundingRect(),Qt::KeepAspectRatio);
    view->show();
    qDebug("end");
}
