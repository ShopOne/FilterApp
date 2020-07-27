#include "mymainwin.hpp"
MyMainWin::MyMainWin(){
  w = new MyWindow();
  mTop = new QWidget();
  mVbox = new QVBoxLayout();
  mHbox = new QHBoxLayout();
  loadAction = new QAction("&Load", this);
  saveAction = new QAction("&Save", this);
  connect(loadAction, SIGNAL(triggered()), this, SLOT(load()));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(loadAction);
  fileMenu->addAction(saveAction);
  addButton("low-pass Filter",b1,SLOT(changeModeLowPass()));
  addButton("high-pass Filter",b1,SLOT(changeModeHighPass()));
  addButton("positive tone-curve Filter",b2,SLOT(changeModePosiTone()));
  addButton("negative tone-curve Filter",b3,SLOT(changeModeNegaTone()));
  addButton("nega-posi Filter",b4,SLOT(changeModeNegaPosi()));
  addButton("mosaic Filter",b5,SLOT(changeModeMosaic()));
  addButton("hough filter",b6,SLOT(changeModeHough()));
  addButton("median filter",b7,SLOT(changeModeMedian()));
  addButton("back image",b8,SLOT(backImageList()));
  mHbox->addWidget(w);
  mHbox->addLayout(mVbox);
  mTop->setLayout(mHbox);
  setCentralWidget(mTop);
}
void MyMainWin::addButton(String name,QPushButton *qb, const char *func){
  qb = new QPushButton(name.c_str());
  connect(qb,SIGNAL(clicked()),w,func);
  mVbox->addWidget(qb);
}
void MyMainWin::load(){
  QString name = QFileDialog::getOpenFileName(
      this,
      "test",
      ".",
      "*.jpg");
  w->changeImage(name);
}
void MyMainWin::save(){
  QString name = QFileDialog::getSaveFileName(this,"test",
      ".","");
  w->saveTopImage(name);
}
