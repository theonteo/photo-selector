#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "Viewport.h"

#include <QMainWindow>
#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printer)
#    include <QPrinter>
#  endif
#endif


QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QGroupBox;
QT_END_NAMESPACE

namespace Photo
{
  class PhotoSelector : public QMainWindow
  {
    Q_OBJECT

  public:
    PhotoSelector(QWidget* parent = nullptr);
    bool loadFile(const QString&);

  private slots:
    void open();
    void saveAs();
    void print();
    void copy();
    void paste();
    void about();

  private:

    Viewport viewport;

    void createActions();
    void updateActions();
    bool saveFile(const QString& fileName);


    //folder buttons
    QGroupBox* AddFolderButtons();
    QGroupBox* AddImageSelector();
    QWidget* centralWidget;


    void AddAllWidgets(QMainWindow* window);

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printer;
#endif

    QAction* saveAsAct;
    QAction* printAct;
    QAction* copyAct;
  };
}

#endif