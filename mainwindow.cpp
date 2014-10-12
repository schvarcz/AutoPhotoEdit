#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    first(true)
{
    ui->setupUi(this);
    directories << "/home/schvarcz/Desktop/balance_test/original/"
                << "/home/schvarcz/Desktop/balance_test/colorEnhanced/"
                << "/home/schvarcz/Desktop/balance_test/whiteBalance/";
    savePath = "/home/schvarcz/Desktop/balance_test/selected/";
    editPath = "/home/schvarcz/Desktop/balance_test/editar/";
    diretory.mkdir(savePath);
    diretory.mkdir(editPath);

    diretory.setPath(savePath);
    listImgsProcessed = diretory.entryList(QStringList("*.jpg"));

    diretory.setPath(directories.at(0));
    listImgs = diretory.entryList(QStringList("*.jpg"));

    aniImgTrans = new QPropertyAnimation(ui->imgWidget,"geometry");
    aniImgTrans->setDuration(300);
    aniImgFade = new QPropertyAnimation(ui->imgAux,"geometry");
    aniImgFade->setDuration(300);
    currentIndex = listImgsProcessed.size();
    currentDirectory = 0;
    showImages(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showImages(int sentido)
{
    if (!first)
    {

        if (sentido ==2)
        {
        }
        aniImgTrans->stop();
        ui->imgAux->setPixmap(ui->imgWidget->pixmap()->copy());

        ui->imgAux->setGeometry(QRect(0,0,desktop.width(),desktop.height()));
        if (sentido ==1)
            ui->imgWidget->setGeometry(QRect(desktop.width()*0.1,desktop.height(),desktop.width()*0.8,desktop.height()*0.8));
        if (sentido ==2)
            ui->imgWidget->setGeometry(QRect(desktop.width()*0.1,-desktop.height(),desktop.width()*0.8,desktop.height()*0.8));
        if (sentido ==3)
            ui->imgWidget->setGeometry(QRect(desktop.width(),desktop.height()*0.1,desktop.width()*0.8,desktop.height()*0.8));;
        if (sentido ==4)
            ui->imgWidget->setGeometry(QRect(-desktop.width(),desktop.height()*0.1,desktop.width()*0.8,desktop.height()*0.8));

        aniImgTrans->setEndValue(QRect(0,0,desktop.width(),desktop.height()));
        aniImgTrans->start();
    }
    else
    {
        ui->imgWidget->setGeometry(QRect(0,0,desktop.width(),desktop.height()));
    }
    ui->imgWidget->setPixmap(QPixmap(directories.at(currentDirectory)+listImgs.at(currentIndex)));
    first = false;
}

void MainWindow::next()
{
    currentIndex++;
    showImages(3);
}
void MainWindow::back()
{
    if (currentIndex > 0)
    {
        currentIndex--;
        QFile::remove(savePath+listImgs.at(currentIndex));
        QFile::remove(editPath+listImgs.at(currentIndex));
        showImages(4);
    }
}

void MainWindow::backwardSelected()
{
    if (currentDirectory > 0)
    {
        currentDirectory--;
        showImages(2);
    }
}

void MainWindow::fordwardSelected()
{
    if (currentDirectory < directories.size()-1)
    {
        currentDirectory++;
        showImages(1);
    }
}

void MainWindow::editSelected()
{
    QFile::copy(directories.at(currentDirectory)+listImgs.at(currentIndex),editPath+listImgs.at(currentIndex));
    next();
}

void MainWindow::originalSelected()
{
    QFile::copy(directories.at(currentDirectory)+listImgs.at(currentIndex),savePath+listImgs.at(currentIndex));
    next();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    QMainWindow::keyReleaseEvent(event);
    switch(event->key())
    {
    case Qt::Key_Left:
        back();
        break;
    case Qt::Key_Right:
        originalSelected();
        break;
    case Qt::Key_Up:
        backwardSelected();
        break;
    case Qt::Key_Down:
        fordwardSelected();
        break;
    case Qt::Key_Escape:
        editSelected();
        break;
    }
}
