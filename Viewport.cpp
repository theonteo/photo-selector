#include "Viewport.h"

#include <QScrollBar>
void Viewport::adjustScrollBar(QScrollBar* scrollBar, double factor)
{
	scrollBar->setValue(int(factor * scrollBar->value()
		+ ((factor - 1) * scrollBar->pageStep() / 2)));
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

//! [10] //! [11]
void Viewport::normalSize()
//! [11] //! [12]
{
	imageLabel->adjustSize();
	scaleFactor = 1.0;
}
//! [12]

//! [13]
void Viewport::fitToWindow()
//! [13] //! [14]
{
	bool fitToWindow = fitToWindowAct->isChecked();
	scrollArea->setWidgetResizable(fitToWindow);
	if (!fitToWindow)
		normalSize();
	updateActions();
}
//! [14]

