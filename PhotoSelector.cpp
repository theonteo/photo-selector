
#include "PhotoSelector.h"

#include "QDefinitions.h"

#include <Viewport.h>


#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printdialog)
#    include <QPrintDialog>
#  endif
#endif
namespace Photo
{
	PhotoSelector::PhotoSelector(QWidget* parent)
		: QMainWindow(parent)
	{
		AddAllWidgets(this);
		setCentralWidget(centralWidget);

		createActions();

		resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
	}


	static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode)
	{
		static bool firstDialog = true;

		if (firstDialog) {
			firstDialog = false;
			const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
			dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
		}

		QStringList mimeTypeFilters;
		const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
			? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
		for (const QByteArray& mimeTypeName : supportedMimeTypes)
			mimeTypeFilters.append(mimeTypeName);
		mimeTypeFilters.sort();
		dialog.setMimeTypeFilters(mimeTypeFilters);
		dialog.selectMimeTypeFilter("image/jpeg");
		dialog.setAcceptMode(acceptMode);
		if (acceptMode == QFileDialog::AcceptSave)
			dialog.setDefaultSuffix("jpg");
	}
	QGroupBox* PhotoSelector::AddFolderButtons()
	{

		QGroupBox* groupBox = new QGroupBox(tr("Non-Exclusive Checkboxes"));
		groupBox->setFlat(true);
		//! [7]

		//! [8]
		QCheckBox* checkBox1 = new QCheckBox(tr("&Checkbox 1"));
		QCheckBox* checkBox2 = new QCheckBox(tr("C&heckbox 2"));
		checkBox2->setChecked(true);
		QCheckBox* tristateBox = new QCheckBox(tr("Tri-&state button"));
		tristateBox->setTristate(true);
		//! [8]
		tristateBox->setCheckState(Qt::PartiallyChecked);


		QLineEdit* inputFolder = new QLineEdit(tr("&Input Folder"));
		QLineEdit* outputFolder = new QLineEdit(tr("&	Output Folder"));


		QLabel* labelInput = new QLabel;
		labelInput->setText("Input Folder");
		QPushButton* inputButton = new QPushButton(tr("&Input Folder"));
		inputButton->setFixedSize(100, 25);
		QLabel* labelOutput = new QLabel;
		labelOutput->setText("Output Folder");
		QPushButton* outputButton = new QPushButton(tr("&Output Folder"));
		outputButton->setFixedSize(100, 25);
		inputFolder->setText(tr("InputFolder"));
		outputFolder->setText(tr("OutputFolder"));


		//! [9]
		QVBoxLayout* vbox = new QVBoxLayout;
		vbox->addWidget(checkBox1);
		vbox->addWidget(checkBox2);
		vbox->addWidget(tristateBox);
		vbox->addWidget(labelInput);
		vbox->addWidget(inputButton);
		vbox->addWidget(inputFolder);
		vbox->addWidget(labelOutput);
		vbox->addWidget(outputButton);
		vbox->addWidget(outputFolder);
		vbox->addStretch(1);
		groupBox->setLayout(vbox);

		return groupBox;

	}
	QGroupBox* PhotoSelector::AddImageSelector()
	{
		QGroupBox* groupBox = new QGroupBox(tr("Image Selector"));
		groupBox->setFlat(true);



		//! [9]
		QVBoxLayout* vbox = new QVBoxLayout;

		for (size_t i = 0; i < 10; ++i)
		{
			QCheckBox* checkBox = new QCheckBox(tr("&Checkbox"));
			vbox->addWidget(checkBox);
		}

		vbox->addStretch(1);
		groupBox->setLayout(vbox);

		return groupBox;
	}
	void PhotoSelector::AddAllWidgets(QMainWindow* window)
	{
		centralWidget = new QWidget(window);
		centralWidget->setObjectName(QString::fromUtf8("centralwidget"));
		QGridLayout* grid = new QGridLayout(centralWidget);

		grid->addWidget(AddFolderButtons(), 0, 0, 1, 1);
		grid->addWidget(AddImageSelector(), 0, 1, 1, 1);
		grid->addWidget(viewport.GetScrollArea(), 1, 0, 1, 1);
		viewport.CreateViewportWidget();
	}
	void PhotoSelector::open()
	{
		QFileDialog dialog(this, tr("Open File"));
		initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

		while (dialog.exec() == QDialog::Accepted && !loader.loadFile(dialog.selectedFiles().constFirst(),viewport.GetImage())) {}
		viewport.setImage(viewport.GetImage());
		updateActions();
		//setWindowFilePath(fileName);
	}
	//! [1]

	void PhotoSelector::saveAs()
	{
		QFileDialog dialog(this, tr("Save File As"));
		initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

		while (dialog.exec() == QDialog::Accepted && !loader.saveFile(dialog.selectedFiles().constFirst(), viewport.GetImage())) {}
	}

	//! [5]
	void PhotoSelector::print()
		//! [5] //! [6]
	{
		const auto& label = viewport.GetImageLabel();


		Q_ASSERT(!label->pixmap(Qt::ReturnByValue).isNull());
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
		//! [6] //! [7]
		QPrintDialog dialog(&printer, this);
		//! [7] //! [8]
		if (dialog.exec()) {
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

	//! [8]

	void PhotoSelector::copy()
	{
#ifndef QT_NO_CLIPBOARD
		QGuiApplication::clipboard()->setImage(viewport.GetImage());
#endif // !QT_NO_CLIPBOARD
	}

#ifndef QT_NO_CLIPBOARD
	static QImage clipboardImage()
	{
		if (const QMimeData* mimeData = QGuiApplication::clipboard()->mimeData()) {
			if (mimeData->hasImage()) {
				const QImage image = qvariant_cast<QImage>(mimeData->imageData());
				if (!image.isNull())
					return image;
			}
		}
		return QImage();
	}
#endif // !QT_NO_CLIPBOARD

	void PhotoSelector::paste()
	{
#ifndef QT_NO_CLIPBOARD
		const QImage newImage = clipboardImage();
		if (newImage.isNull()) {
			statusBar()->showMessage(tr("No image in clipboard"));
		}
		else {



			viewport.setImage(newImage);
			updateActions();
			setWindowFilePath(QString());
			const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
				.arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
			statusBar()->showMessage(message);
		}
#endif // !QT_NO_CLIPBOARD
	}


	void PhotoSelector::about()
	{

	}

	void PhotoSelector::createActions()
	{
		QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

		QAction* openAct = fileMenu->addAction(tr("&Open..."), this, &PhotoSelector::open);
		openAct->setShortcut(QKeySequence::Open);

		saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &PhotoSelector::saveAs);
		saveAsAct->setEnabled(false);

		printAct = fileMenu->addAction(tr("&Print..."), this, &PhotoSelector::print);
		printAct->setShortcut(QKeySequence::Print);
		printAct->setEnabled(false);

		fileMenu->addSeparator();

		QAction* exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
		exitAct->setShortcut(tr("Ctrl+Q"));

		QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));

		copyAct = editMenu->addAction(tr("&Copy"), this, &PhotoSelector::copy);
		copyAct->setShortcut(QKeySequence::Copy);
		copyAct->setEnabled(false);

		QAction* pasteAct = editMenu->addAction(tr("&Paste"), this, &PhotoSelector::paste);
		pasteAct->setShortcut(QKeySequence::Paste);

		QMenu* viewMenu = menuBar()->addMenu(tr("&View"));


		QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

		helpMenu->addAction(tr("&About"), this, &PhotoSelector::about);
		helpMenu->addAction(tr("About &Qt"), this, &QApplication::aboutQt);
	}

	void PhotoSelector::updateActions()
	{
		const auto& image = viewport.GetImage();

		saveAsAct->setEnabled(!image.isNull());
		copyAct->setEnabled(!image.isNull());
		//zoomInAct->setEnabled(!fitToWindowAct->isChecked());
		//zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
		//normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
	}
}