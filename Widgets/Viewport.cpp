#include "Widgets/Viewport.h"

#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>
#include <QColorSpace>
#include <QMenu>
#include <QObject>
namespace Photo
{
	Viewport::Viewport()
	{
		imageLabel = std::make_unique< QLabel>();
		scrollArea = std::make_unique< QScrollArea>(&*imageLabel);
	}

	void Viewport::adjustScrollBar(QScrollBar* scrollBar, double factor)
	{
		scrollBar->setValue(int(factor * scrollBar->value()
			+ ((factor - 1) * scrollBar->pageStep() / 2)));
	}

	void Viewport::CreateViewportWidget()
	{
		scrollArea->setBackgroundRole(QPalette::Base);
		scrollArea->setWidget(&*imageLabel);
		scrollArea->setVisible(true);


	}
	const std::unique_ptr<QWidget>& Viewport::GetViewportWidget() const
	{
		return widget;
	}
	const std::unique_ptr<QScrollArea>& Viewport::GetScrollArea() const
	{
		return scrollArea;
	}
	const std::unique_ptr<QLabel>& Viewport::GetImageLabel() const
	{
		return imageLabel;
	}

	const QImage& Viewport::GetImage() const
	{
		return image;
	}

	QImage& Viewport::GetImage()
	{
		return image;
	}

	void Viewport::setImage(const QImage& newImage)
	{
		image = newImage;
		if (image.colorSpace().isValid())
			image.convertToColorSpace(QColorSpace::SRgb);
		imageLabel->setPixmap(QPixmap::fromImage(image));
		//! [4]
		scaleFactor =1.0;

		scrollArea->setVisible(true);
		//printAct->setEnabled(true);
		//fitToWindowAct->setEnabled(true);
		//updateActions();

	//	if (!fitToWindowAct->isChecked())
		imageLabel->adjustSize();
		zoomOut();

	}

	void Viewport::zoomIn()
	{
		scaleImage(1.25);
	}

	void Viewport::zoomOut()
	{
		scaleImage(0.8);
	}

	void Viewport::normalSize()
	{
		imageLabel->adjustSize();
		scaleFactor = 1.0;
	}

	void Viewport::fitToWindow()
	{
		//bool fitToWindow = fitToWindowAct->isChecked();
	//	scrollArea->setWidgetResizable(fitToWindow);
	//	if (!fitToWindow)
		normalSize();
		//	updateActions();
	}

	void Viewport::AddActions(QMenu* menu)
	{
		zoomInAct = menu->addAction(tr("Zoom &In (25%)"), this, &Viewport::zoomIn);
		zoomInAct->setShortcut(QKeySequence::ZoomIn);
		zoomInAct->setEnabled(false);

		zoomOutAct = menu->addAction(tr("Zoom &Out (25%)"), this, &Viewport::zoomOut);
		zoomOutAct->setShortcut(QKeySequence::ZoomOut);
		zoomOutAct->setEnabled(false);

		normalSizeAct = menu->addAction(tr("&Normal Size"), this, &Viewport::normalSize);
		normalSizeAct->setShortcut(tr("Ctrl+S"));
		normalSizeAct->setEnabled(false);

		menu->addSeparator();

		fitToWindowAct = menu->addAction(tr("&Fit to Window"), this, &Viewport::fitToWindow);
		fitToWindowAct->setEnabled(false);
		fitToWindowAct->setCheckable(true);
		fitToWindowAct->setShortcut(tr("Ctrl+F"));
	}


	void Viewport::scaleImage(double factor)
	{
		scaleFactor*= factor;
		const auto& res = imageLabel->pixmap(Qt::ReturnByValue).size();
		imageLabel->resize(scaleFactor * res);

		adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
		adjustScrollBar(scrollArea->verticalScrollBar(), factor);

		//	zoomInAct->setEnabled(scaleFactor < 3.0);
		//	zoomOutAct->setEnabled(scaleFactor > 0.333);
	}
}