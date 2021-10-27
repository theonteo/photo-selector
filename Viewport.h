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

  QWidget* widget;


public:

  //get reference of image label
  const QLabel* GetImageLabel() const;

  //get reference of image
  const QImage& GetImage() const;

  //image functions
  void setImage(const QImage& newImage);
  void adjustScrollBar(QScrollBar* scrollBar, double factor);

  QWidget* CreateViewportWidget();

  //scaling functions
  void scaleImage(double factor);
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();

};

