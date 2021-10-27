
#include "imageviewer.h"

#include <QApplication>
#include <QClipboard>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QScreen>
#include <QStandardPaths>
#include <QStatusBar>
#include <QtWidgets/QStackedWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <qlineedit.h>

#include <Viewport.h>


#if defined(QT_PRINTSUPPORT_LIB)
#  include <QtPrintSupport/qtprintsupportglobal.h>

#  if QT_CONFIG(printdialog)
#    include <QPrintDialog>
#  endif
#endif

//! [0]
ImageViewer::ImageViewer(QWidget* parent)
	: QMainWindow(parent)
{


	AddAllWidgets(this);
setCentralWidget(centralWidget);


	createActions();

	resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

//! [0]
//! [2]

bool ImageViewer::loadFile(const QString& fileName)
{
	QImageReader reader(fileName);
	reader.setAutoTransform(true);
	const QImage newImage = reader.read();
	if (newImage.isNull()) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load %1: %2")
			.arg(QDir::toNativeSeparators(fileName), reader.errorString()));
		return false;
	}
	//! [2]

	viewport.setImage(newImage);

	setWindowFilePath(fileName);

	const QString description = image.colorSpace().isValid()
		? image.colorSpace().description() : tr("unknown");
	const QString message = tr("Opened \"%1\", %2x%3, Depth: %4 (%5)")
		.arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height())
		.arg(image.depth()).arg(description);
	statusBar()->showMessage(message);
	return true;
}
//! [4]

bool ImageViewer::saveFile(const QString& fileName)
{
	QImageWriter writer(fileName);

	if (!writer.write(image)) {
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot write %1: %2")
			.arg(QDir::toNativeSeparators(fileName), writer.errorString()));
		return false;
	}
	const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
	statusBar()->showMessage(message);
	return true;
}

//! [1]

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
QGroupBox* ImageViewer::AddFolderButtons()
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

	QLabel* labelOutput = new QLabel;
	labelOutput->setText("Output Folder");

	inputFolder->setText(tr("InputFolder"));
	outputFolder->setText(tr("OutputFolder"));


	//! [9]
	QVBoxLayout* vbox = new QVBoxLayout;
	vbox->addWidget(checkBox1);
	vbox->addWidget(checkBox2);
	vbox->addWidget(tristateBox);
	vbox->addWidget(labelInput);
	vbox->addWidget(inputFolder);
	vbox->addWidget(labelOutput);
	vbox->addWidget(outputFolder);
	vbox->addStretch(1);
	groupBox->setLayout(vbox);

	return groupBox;

}
QGroupBox* ImageViewer::AddImageSelector()
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
void ImageViewer::AddAllWidgets(QMainWindow* window)
{
	centralWidget = new QWidget(window);
	centralWidget->setObjectName(QString::fromUtf8("centralwidget"));
	QGridLayout* grid = new QGridLayout(centralWidget);

	grid->addWidget(AddFolderButtons(), 0, 0,1,1);
	grid->addWidget(AddImageSelector(), 0, 1, 1, 1);
	QLabel* selector = new QLabel;
	selector->setText("Selector");

	grid->addWidget(scrollArea, 1, 0, 1, 1);

	//imageLabel->setBackgroundRole(QPalette::Base);
	//imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	//imageLabel->setScaledContents(true);

	scrollArea->setBackgroundRole(QPalette::Base);
	scrollArea->setWidget(imageLabel);
	scrollArea->setVisible(true);

}
void ImageViewer::open()
{
	QFileDialog dialog(this, tr("Open File"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

	while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().constFirst())) {}
}
//! [1]

void ImageViewer::saveAs()
{
	QFileDialog dialog(this, tr("Save File As"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

	while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().constFirst())) {}
}

//! [5]
void ImageViewer::print()
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

void ImageViewer::copy()
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

void ImageViewer::paste()
{
#ifndef QT_NO_CLIPBOARD
	const QImage newImage = clipboardImage();
	if (newImage.isNull()) {
		statusBar()->showMessage(tr("No image in clipboard"));
	}
	else {



		viewport.setImage(newImage);
		setWindowFilePath(QString());
		const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
			.arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
		statusBar()->showMessage(message);
	}
#endif // !QT_NO_CLIPBOARD
}


void ImageViewer::about()
{

}

void ImageViewer::createActions()
{
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

	QAction* openAct = fileMenu->addAction(tr("&Open..."), this, &ImageViewer::open);
	openAct->setShortcut(QKeySequence::Open);

	saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &ImageViewer::saveAs);
	saveAsAct->setEnabled(false);

	printAct = fileMenu->addAction(tr("&Print..."), this, &ImageViewer::print);
	printAct->setShortcut(QKeySequence::Print);
	printAct->setEnabled(false);

	fileMenu->addSeparator();

	QAction* exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
	exitAct->setShortcut(tr("Ctrl+Q"));

	QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));

	copyAct = editMenu->addAction(tr("&Copy"), this, &ImageViewer::copy);
	copyAct->setShortcut(QKeySequence::Copy);
	copyAct->setEnabled(false);

	QAction* pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageViewer::paste);
	pasteAct->setShortcut(QKeySequence::Paste);

	QMenu* viewMenu = menuBar()->addMenu(tr("&View"));

	zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &Viewport::zoomIn);
	zoomInAct->setShortcut(QKeySequence::ZoomIn);
	zoomInAct->setEnabled(false);

	zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &Viewport::zoomOut);
	zoomOutAct->setShortcut(QKeySequence::ZoomOut);
	zoomOutAct->setEnabled(false);

	normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &Viewport::normalSize);
	normalSizeAct->setShortcut(tr("Ctrl+S"));
	normalSizeAct->setEnabled(false);

	viewMenu->addSeparator();

	fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &Viewport::fitToWindow);
	fitToWindowAct->setEnabled(false);
	fitToWindowAct->setCheckable(true);
	fitToWindowAct->setShortcut(tr("Ctrl+F"));

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));

	helpMenu->addAction(tr("&About"), this, &ImageViewer::about);
	helpMenu->addAction(tr("About &Qt"), this, &QApplication::aboutQt);
}

void ImageViewer::updateActions()
{
	const auto& image = viewport.GetImage();

	saveAsAct->setEnabled(!image.isNull());
	copyAct->setEnabled(!image.isNull());
	zoomInAct->setEnabled(!fitToWindowAct->isChecked());
	zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
	normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}