/*****************************************************************************/
/*!
\file PhotoSelector.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "App/PhotoSelector.h"
#include "App/QDefinitions.h"
#include <Widgets/Viewport.h>

#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printdialog)
#    include <QPrintDialog>
#  endif
#endif

namespace PhotoSelector
{
	/**************************************************************************/
	/*
		 \brief class constructor
	*/
	/**************************************************************************/
	PhotoSelector::PhotoSelector(QWidget* parent)
		: QMainWindow(parent)
	{
		AddAllWidgets();
		setCentralWidget(&*centralWidget);

		createActions();
		resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
	}
	/**************************************************************************/
	/*
		 \brief opens a file dialog to choose photos
	*/
	/**************************************************************************/
	static void initializeImageFileDialog
	(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode)
	{
		static bool firstDialog = true;

		if (firstDialog) 
		{
			firstDialog = false;
			const QStringList picturesLocations =
				QStandardPaths::standardLocations
				(QStandardPaths::PicturesLocation);

			dialog.setDirectory
			(picturesLocations.isEmpty()
				? QDir::currentPath() : picturesLocations.last());
		}

		QStringList mimeTypeFilters;
		const QByteArrayList supportedMimeTypes
			= acceptMode == QFileDialog::AcceptOpen
			? QImageReader::supportedMimeTypes() 
			: QImageWriter::supportedMimeTypes();

		for (const QByteArray& mimeTypeName : supportedMimeTypes)
			mimeTypeFilters.append(mimeTypeName);
		mimeTypeFilters.sort();
		dialog.setMimeTypeFilters(mimeTypeFilters);
		dialog.selectMimeTypeFilter("image/jpeg");
		dialog.setAcceptMode(acceptMode);

		if (acceptMode == QFileDialog::AcceptSave)
			dialog.setDefaultSuffix("jpg");
	}
/**************************************************************************/
/*
	 \brief generate widget for folder
*/
/**************************************************************************/
	const std::unique_ptr<QGroupBox>& PhotoSelector::AddFolderButtons()
	{
		folder.GenerateWidgets();
		return folder.GetGroupBox();
	}
	/**************************************************************************/
	/*
		 \brief generate widget for image selector
	*/
	/**************************************************************************/
	const std::unique_ptr < QScrollArea>& PhotoSelector::AddImageSelector()
	{
		 selector.GenerateWidgets();
		 return selector.GetScrollArea();
	}
	/**************************************************************************/
	/*
		 \brief add all widgets to current window
	*/
	/**************************************************************************/
	void PhotoSelector::AddAllWidgets()
	{
		centralWidget = std::make_unique< QWidget>(this);
		centralWidget->setObjectName(QString::fromUtf8("centralwidget"));
		QGridLayout* grid = new QGridLayout(&*centralWidget);

		grid->addWidget(&*AddFolderButtons(), 0, 0, 1, 1);
		grid->addWidget(&*AddImageSelector(), 0, 1, 2, 1);
		grid->addWidget(&*viewport.GetScrollArea(), 1, 0, 1, 1);

		viewport.CreateViewportWidget();
	}
	/**************************************************************************/
	/*
		 \brief open a image
	*/
	/**************************************************************************/
	void PhotoSelector::open(const QString& str)
	{
		const auto& openStr = 
			loader.loadFile(str, viewport.GetImage());

		viewport.setImage(viewport.GetImage());
		updateActions();

	}
	/**************************************************************************/
	/*
		 \brief save image file
	*/
	/**************************************************************************/
	void PhotoSelector::saveAs()
	{
		QFileDialog dialog(this, tr("Save File As"));
		initializeImageFileDialog
		(dialog, QFileDialog::AcceptSave);

		while (dialog.exec() == QDialog::Accepted && !loader.saveFile
		(dialog.selectedFiles().constFirst(), viewport.GetImage())) {}
	}
	/**************************************************************************/
	/*
		 \brief print image file
	*/
	/**************************************************************************/
	void PhotoSelector::print()
	{
		const auto& label = viewport.GetImageLabel();


		Q_ASSERT(!label->pixmap(Qt::ReturnByValue).isNull());
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
		QPrintDialog dialog(&printer, this);

		if (dialog.exec()) 
		{
			QPainter painter(&printer);
			QPixmap pixmap = label->pixmap(Qt::ReturnByValue);
			QRect rect = painter.viewport();
			QSize size = pixmap.size();
			size.scale(rect.size(), Qt::KeepAspectRatio);
			painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
			painter.setWindow(pixmap.rect());
			painter.drawPixmap(0, 0, pixmap);
		}
#endif
	}
	/**************************************************************************/
	/*
		 \brief copies image
	*/
	/**************************************************************************/
	void PhotoSelector::copy()
	{
#ifndef QT_NO_CLIPBOARD
		QGuiApplication::clipboard()->setImage(viewport.GetImage());
#endif // !QT_NO_CLIPBOARD
	}
	/**************************************************************************/
	/*
		 \brief put image to clipboard
	*/
	/**************************************************************************/
#ifndef QT_NO_CLIPBOARD
	static QImage clipboardImage()
	{
		if (const QMimeData* mimeData = QGuiApplication::clipboard()->mimeData()) 
		{
			if (mimeData->hasImage()) 
			{
				const QImage image = qvariant_cast<QImage>(mimeData->imageData());
				if (!image.isNull())
					return image;
			}
		}
		return QImage();
	}
#endif // !QT_NO_CLIPBOARD
	/**************************************************************************/
	/*
		 \brief paste image from clipboard
	*/
	/**************************************************************************/
	void PhotoSelector::paste()
	{
#ifndef QT_NO_CLIPBOARD
		const QImage newImage = clipboardImage();
		if (newImage.isNull())
			statusBar()->showMessage(tr("No image in clipboard"));
		else
		{
			viewport.setImage(newImage);
			updateActions();
			setWindowFilePath(QString());
			const QString message = 
				tr("Obtained image from clipboard, %1x%2, Depth: %3")
				.arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());

			statusBar()->showMessage(message);
		}
#endif // !QT_NO_CLIPBOARD
	}
	/**************************************************************************/
	/*
		 \brief create file actions
	*/
	/**************************************************************************/
	void PhotoSelector::createActions()
	{
		QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

		saveAsAct = fileMenu->addAction
		(tr("&Save As..."), this, &PhotoSelector::saveAs);
		saveAsAct->setEnabled(false);

		printAct = fileMenu->addAction
		(tr("&Print..."), this, &PhotoSelector::print);
		printAct->setShortcut(QKeySequence::Print);
		printAct->setEnabled(false);

		fileMenu->addSeparator();

		QAction* exitAct = fileMenu->addAction
		(tr("E&xit"), this, &QWidget::close);
		exitAct->setShortcut(tr("Ctrl+Q"));

		QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));

		copyAct = editMenu->addAction
		(tr("&Copy"), this, &PhotoSelector::copy);
		copyAct->setShortcut(QKeySequence::Copy);
		copyAct->setEnabled(false);

		QAction* pasteAct = editMenu->addAction
		(tr("&Paste"), this, &PhotoSelector::paste);
		pasteAct->setShortcut(QKeySequence::Paste);

		QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
		QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

		helpMenu->addAction(tr("About "), this, &QApplication::aboutQt);
	}
	/**************************************************************************/
	/*
		 \brief update file actions
	*/
	/**************************************************************************/
	void PhotoSelector::updateActions()
	{
		const auto& image = viewport.GetImage();

		saveAsAct->setEnabled(!image.isNull());
		copyAct->setEnabled(!image.isNull());
	}
	/**************************************************************************/
	/*
		 \brief returns folder
	*/
	/**************************************************************************/
	const Folder& PhotoSelector::GetFolder() const
	{
		return folder;
	}
	/**************************************************************************/
	/*
		 \brief returns folder
	*/
	/**************************************************************************/
	Folder& PhotoSelector::GetFolder()
	{
		return folder;
	}
	/**************************************************************************/
	/*
		 \brief returns selector
	*/
	/**************************************************************************/
	const Selector& PhotoSelector::GetSelector() const
	{
		return selector;
	}
	/**************************************************************************/
	/*
		 \brief returns selector
	*/
	/**************************************************************************/
	Selector& PhotoSelector::GetSelector()
	{
		return selector;
	}
}