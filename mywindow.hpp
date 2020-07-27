#pragma once
#include<QtGui>
#include<QTimer>
#include<QImage>
#include<QWidget>
#include<QLabel>
#include<QString>
#include<vector>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
enum FilterMode{
  HIGHPASS,
  LOWPASS,
  POSI_TONE_CURVE,
  NEGA_TONE_CURVE,
  NEGA_POSI,
  MOSAIC,
  HOUGH,
  MEDIAN,
  NONE,
};
class MyWindow : public QWidget{
  Q_OBJECT
  public:
    MyWindow(QWidget *parent=0);
    void changeImage(QString);
    void saveTopImage(QString);
  public slots:
    void changeModeHighPass();
    void changeModePosiTone();
    void changeModeNegaTone();
    void changeModeLowPass();
    void changeModeNegaPosi();
    void changeModeMosaic();
    void changeModeHough();
    void changeModeMedian();
    void backImageList();
  protected:
    void paintEvent(QPaintEvent*);
  private:
    void changeImage();
    void changeMode(FilterMode);
    void initialize();
    void highpassFilter(Mat); 
    void posiToneCurveFilter(Mat); 
    void negaToneCurveFilter(Mat); 
    void lowpassFilter(Mat); 
    void negaPosiFilter(Mat); 
    void mosaicFilter(Mat);
    void houghFilter(Mat);
    void medianFilter(Mat);
    QTimer mTimer;
    QImage mImage;
    std::vector<QImage> imageList;
    FilterMode mode;
};
