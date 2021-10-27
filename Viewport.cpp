#include "Viewport.h"

#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>
#include <QColorSpace>

void Viewport::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()
		+ ((factor - 1) * scrollBar->pageStep() / 2)));
}

const QLabel* Viewport::GetImageLabel() const
{
	return imageLabel;
}

const QImage& Viewport::GetImage() const
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
	scaleFactor = 1.0;

	scrollArea->setVisible(true);
	printAct->setEnabled(true);
	fitToWindowAct->setEnabled(true);
	updateActions();

	if (!fitToWindowAct->isChecked())
		imageLabel->adjustSize();
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
	bool fitToWindow = fitToWindowAct->isChecked();
	scrollArea->setWidgetResizable(fitToWindow);
	if (!fitToWindow)
		normalSize();
	updateActions();
}


void Viewport::scaleImage(double factor)
{
	scaleFactor *= factor;
	imageLabel->resize(scaleFactor * imageLabel->pixmap(Qt::ReturnByValue).size());

	adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
	adjustScrollBar(scrollArea->verticalScrollBar(), factor);

	zoomInAct->setEnabled(scaleFactor < 3.0);
	zoomOutAct->setEnabled(scaleFactor > 0.333);
}
