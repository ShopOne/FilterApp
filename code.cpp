#include "mywindow.hpp"
#include "mymainwin.hpp"
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
using namespace cv;
int main(int argc, char *argv[]){
  QApplication a(argc, argv);
  MyMainWin w;
  w.show();
  return a.exec();
}
