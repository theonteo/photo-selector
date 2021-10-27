#pragma once

#include <QImage>
#include <QObject>
QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QGroupBox;
class QMenu;
class QWidget;
class QObject;
QT_END_NAMESPACE

class Viewport:public QObject
{
  Q_OBJECT
private:

  QImage image;
  QLabel* imageLabel{ nullptr };
  QScrollArea* scrollArea{ nullptr };
  double scaleFactor = 1;

  QWidget* widget{ nullptr };

  QAction* zoomInAct;
  QAction* zoomOutAct;
  QAction* normalSizeAct;
  QAction* fitToWindowAct;

public:
  Viewport();

  void CreateViewportWidget();

  //get reference of image label
  const QLabel* GetImageLabel() const;

  //get reference of image
  const QImage& GetImage() const;

  //image functions
  void setImage(const QImage& newImage);
  void adjustScrollBar(QScrollBar* scrollBar, double factor);

  QWidget* GetViewportWidget() const;

  //scaling functions
  void scaleImage(double factor);
private slots:
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();

  void AddActions(QMenu* menu);





};

