#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "Viewport.h"
#include "ImageLoader.h"


#include <QMainWindow>
#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printer)
#    include <QPrinter>
#  endif
#endif

#include "Folder.h"
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
  private slots:
    void open();
    void saveAs();
    void print();
    void copy();
    void paste();
    void about();

  private:

    Viewport viewport;
    ImageLoader loader;
    Folder folder;

    void createActions();
    void updateActions();

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
