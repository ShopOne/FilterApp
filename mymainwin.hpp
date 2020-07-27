#pragma once
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QFileDialog>
#include <QMenuBar>
#include "mywindow.hpp"
class MyMainWin : public QMainWindow{
  Q_OBJECT
  public:
    MyMainWin();
  private slots:
    void load();
    void save();
  private:
    void addButton(String,QPushButton*,const char*);
    QPushButton *b0,*b1,*b2,*b3,*b4;
    QPushButton *b5,*b6,*b7,*b8;
    QMenu *fileMenu;
    QAction *loadAction,*saveAction;
    MyWindow *w;
    QHBoxLayout *mHbox;
    QVBoxLayout *mVbox;
    QWidget *mTop;
};
