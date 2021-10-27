#pragma once

#include <QImage>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QGroupBox;
QT_END_NAMESPACE

class Viewport
{
	Q_OBJECT

private:

  QImage image;
  QLabel* imageLabel;
  QScrollArea* scrollArea;
  double scaleFactor = 1;

  //image functions
  void setImage(const QImage& newImage);
  void adjustScrollBar(QScrollBar* scrollBar, double factor);

  //scaling functions
  void scaleImage(double factor);
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();


public:

private:


};

