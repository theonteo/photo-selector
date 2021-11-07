#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "Widgets/Viewport.h"
#include "Image/ImageLoader.h"
#include "Widgets/Folder.h"
#include "Widgets/Selector.h"

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
	public:
		PhotoSelector(QWidget* parent = nullptr);

	public slots:
		void open(const QString& str);
		void saveAs();
		void print();
		void copy();
		void paste();

	private:

		//custom widgets for app
		Viewport viewport;
		ImageLoader loader;
		Folder folder;
		Selector selector;


		void createActions();
		void updateActions();

		//folder buttons
		const std::unique_ptr<QGroupBox>& AddFolderButtons();
		const std::unique_ptr < QScrollArea>& AddImageSelector();
		std::unique_ptr < QWidget> centralWidget;

		void AddAllWidgets();


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
