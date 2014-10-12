#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QKeyEvent>
#include <qmath.h>
#include <QDesktopWidget>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QString savePath, editPath;
    QStringList listImgs, listImgsProcessed, directories;
    QDir diretory;
    QDesktopWidget desktop;
    int currentIndex, currentDirectory;
    QPropertyAnimation *aniImgTrans, *aniImgFade;
    bool first;

    void showImages(int sentido);

private slots:
    void next();
    void back();
    void backwardSelected();
    void fordwardSelected();
    void originalSelected();
    void editSelected();
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
