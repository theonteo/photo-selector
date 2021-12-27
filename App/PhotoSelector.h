/*****************************************************************************/
/*!
\file PhotoSelector.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#ifndef PHOTOSELECTOR_H
#define PHOTOSELECTOR_H

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

namespace PhotoSelector
{
	class PhotoSelector final : public QMainWindow
	{
	public:
		//constructor
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
		
		std::unique_ptr < QWidget> centralWidget;

		//action funcs
		void createActions();
		void updateActions();

		//widget func - collate all widgets
		void AddAllWidgets();

		//folder buttons
		const std::unique_ptr<QGroupBox>& AddFolderButtons();
		const std::unique_ptr < QScrollArea>& AddImageSelector();

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

		const Viewport& GetViewport() const;
		Viewport& GetViewport();
	};
}

#endif
