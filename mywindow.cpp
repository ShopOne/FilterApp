#include "mywindow.hpp"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
void MyWindow::initialize(){
  imageList.push_back(QImage(WINDOW_WIDTH,WINDOW_HEIGHT,QImage::Format_RGB888));
  setMinimumSize(WINDOW_WIDTH,WINDOW_HEIGHT);
}
int clamp(double x,int l,int r){
  if(x<l) return l;
  if(x>r) return r;
  return x;
}
Mat to_Mat(QImage image){
  image = image.rgbSwapped();
  return cv::Mat( image.height(), image.width(),
      CV_8UC3,
      const_cast<uchar*>(image.bits()),
      static_cast<size_t>(image.bytesPerLine())
      ).clone();
}
QImage to_QImage(Mat cv){
  QImage img(cv.data, cv.cols, cv.rows, QImage::Format_RGB888);
  return img.rgbSwapped();
}
void MyWindow::changeImage(QString qs){
  Mat src = cv::imread(qs.toStdString());
  QImage img(src.data,src.cols,src.rows,QImage::Format_RGB888);
  img = img.rgbSwapped();
  imageList.push_back(img);
  update();
}
void MyWindow::posiToneCurveFilter(Mat img){
  for(int y=0;y<img.rows;y++){
    Vec3b* p = img.ptr<Vec3b>(y);
    for(int x=0;x<img.cols;x++){
      Vec3b bgr = p[x];
      bgr[0] = clamp(bgr[0]*1.2,0,255);
      bgr[1] = clamp(bgr[1]*1.2,0,255);
      bgr[2] = clamp(bgr[2]*1.2,0,255);
      p[x] = bgr;
    }
  }
  imageList.push_back(to_QImage(img));
}
void MyWindow::negaToneCurveFilter(Mat img){
  for(int y=0;y<img.rows;y++){
    Vec3b* p = img.ptr<Vec3b>(y);
    for(int x=0;x<img.cols;x++){
      Vec3b bgr = p[x];
      bgr[0] = clamp(bgr[0]*0.8,0,255);
      bgr[1] = clamp(bgr[1]*0.8,0,255);
      bgr[2] = clamp(bgr[2]*0.8,0,255);
      p[x] = bgr;
    }
  }
  imageList.push_back(to_QImage(img));
}
void MyWindow::changeMode(FilterMode f){
  mode = f;
  this->changeImage();
}
void MyWindow::changeModeMedian(){
  changeMode(MEDIAN);
}
void MyWindow::changeModeLowPass(){
  changeMode(HIGHPASS);
}
void MyWindow::changeModeHighPass(){
  changeMode(LOWPASS);
}
void MyWindow::changeModePosiTone(){
  changeMode(POSI_TONE_CURVE);
}
void MyWindow::changeModeNegaTone(){
  changeMode(NEGA_TONE_CURVE);
}
void MyWindow::changeModeNegaPosi(){
  changeMode(NEGA_POSI);
}
void MyWindow::changeModeMosaic(){
  changeMode(MOSAIC);
}
void MyWindow::changeModeHough(){
  changeMode(HOUGH);
}
MyWindow::MyWindow(QWidget *parent) :QWidget(parent){
  initialize();
}
void MyWindow::paintEvent(QPaintEvent *event){
  QPainter painter(this);
  if(imageList.empty()) return;
  painter.drawImage(0,0,imageList.back());
}
void MyWindow::changeImage(){
  if(imageList.empty()) return;
  switch(mode){
    case HIGHPASS:
      lowpassFilter(to_Mat(imageList.back()));
      break;
    case LOWPASS:
      highpassFilter(to_Mat(imageList.back()));
      break;
    case POSI_TONE_CURVE:
      posiToneCurveFilter(to_Mat(imageList.back()));
      break;
    case NEGA_TONE_CURVE:
      negaToneCurveFilter(to_Mat(imageList.back()));
      break;
    case NEGA_POSI:
      negaPosiFilter(to_Mat(imageList.back()));
      break;
    case MOSAIC:
      mosaicFilter(to_Mat(imageList.back()));
      break;
    case HOUGH:
      houghFilter(to_Mat(imageList.back()));
      break;
    case MEDIAN:
      medianFilter(to_Mat(imageList.back()));
      break;
    default:
      break;
  }
  update();
}

void MyWindow::highpassFilter(Mat src) { 
  Mat dst = src.clone();;
  char cf[3][3] = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
  Mat filter = Mat(3,3,CV_8S,cf);
  filter2D(src, dst,
      -1,filter);
  imageList.push_back(to_QImage(dst));
} 
void MyWindow::lowpassFilter(Mat src) {
  Mat dst = src.clone();
  blur(src, dst,Size(11,11));
  imageList.push_back(to_QImage(dst));
} 
void MyWindow::negaPosiFilter(Mat src) {
  Mat dst = ~(src.clone());
  imageList.push_back(to_QImage(dst));
}
void MyWindow::mosaicFilter(Mat src){
  Mat dst = src.clone();
  Size blockSize = Size(10,10);
  cv::resize(src, dst, Size(), 1.0/(double)blockSize.width, 1.0/(double)blockSize.height);
  cv::resize(dst, dst, src.size(), blockSize.width, blockSize.height, INTER_NEAREST);
  imageList.push_back(to_QImage(dst));
}
void MyWindow::medianFilter(Mat src){
  Mat dst = src.clone();
  medianBlur(src,dst,11);
  imageList.push_back(to_QImage(dst));
}
void MyWindow::houghFilter(Mat src){
  Mat dst = src.clone(),work;
  cvtColor(src, work, COLOR_BGR2GRAY);
  Canny(work, work, 50, 200, 3);

  std::vector<Vec4i> lines;
  HoughLinesP(work, lines, 1, CV_PI/180, 50, 50, 10);
  for(auto itr =lines.begin();itr!=lines.end();itr++){
    Vec4i l = *itr;
    line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 2);
  }
  imageList.push_back(to_QImage(dst));
}
void MyWindow::backImageList() {
  if(imageList.empty()) return;
  imageList.pop_back();
  update();
}
void MyWindow::saveTopImage(QString qs){
  if(imageList.empty()) return;
  imageList.back().save(qs);
}
