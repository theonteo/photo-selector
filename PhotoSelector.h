#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "Viewport.h"
#include "ImageLoader.h"
#include "Folder.h"
#include "Selector.h"

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

	private slots:
		void open();
		void saveAs();
		void print();
		void copy();
		void paste();
		void about();

	private:

		//custom widgets for app
		Viewport viewport;
		ImageLoader loader;
		Folder folder;
		Selector selector;


		void createActions();
		void updateActions();

		//folder buttons
		QGroupBox* AddFolderButtons();
		QScrollArea* AddImageSelector();
		QWidget* centralWidget;

		void AddAllWidgets(QMainWindow* window);


#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
		QPrinter printer;
#endif

		QAction* saveAsAct;
		QAction* printAct;
		QAction* copyAct;

	public:
		const Folder& GetFolder() const;
		Folder& GetFolder();

		const Selector& GetSelector() const;
		Selector& GetSelector();
	};
}

#endif
