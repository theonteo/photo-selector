/*****************************************************************************/
/*!
\file Viewport.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "Widgets/Viewport.h"
#include "App/QDefinitions.h"

namespace PhotoSelector
{
	/**************************************************************************/
	/*
		 \brief constructor
	*/
	/**************************************************************************/
	Viewport::Viewport()
	{
		imageLabel = std::make_unique< QLabel>();
		scrollArea = std::make_unique< QScrollArea>(&*imageLabel);
	}
	/**************************************************************************/
	/*
		 \brief  adjusting of scroll bar
	*/
	/**************************************************************************/
	void Viewport::adjustScrollBar(QScrollBar* scrollBar, double factor)
	{
		scrollBar->setValue(int(factor * scrollBar->value()
			+ ((factor - 1) * scrollBar->pageStep() / 2)));
	}
	/**************************************************************************/
	/*
		 \brief  viewport widget creation
	*/
	/**************************************************************************/
	void Viewport::CreateViewportWidget()
	{
		scrollArea->setBackgroundRole(QPalette::Base);
		scrollArea->setWidget(&*imageLabel);
		scrollArea->setVisible(true);
	}
	/**************************************************************************/
	/*
		 \brief  return viewport widget
	*/
	/**************************************************************************/
	const std::unique_ptr<QWidget>& Viewport::GetViewportWidget() const
	{
		return widget;
	}
	/**************************************************************************/
	/*
		 \brief return scroll area
	*/
	/**************************************************************************/
	const std::unique_ptr<QScrollArea>& Viewport::GetScrollArea() const
	{
		return scrollArea;
	}
	/**************************************************************************/
	/*
		 \brief  return image label
	*/
	/**************************************************************************/
	const std::unique_ptr<QLabel>& Viewport::GetImageLabel() const
	{
		return imageLabel;
	}
	/**************************************************************************/
	/*
		 \brief return image
	*/
	/**************************************************************************/
	const QImage& Viewport::GetImage() const
	{
		return image;
	}
	/**************************************************************************/
	/*
		 \brief retrun image
	*/
	/**************************************************************************/
	QImage& Viewport::GetImage()
	{
		return image;
	}
	/**************************************************************************/
	/*
		 \brief set image to viewport
	*/
	/**************************************************************************/
	void Viewport::setImage(const QImage& newImage)
	{
		image = newImage;
		if (image.colorSpace().isValid())
			image.convertToColorSpace(QColorSpace::SRgb);
		imageLabel->setPixmap(QPixmap::fromImage(image));
		scaleFactor =1.0;

		scrollArea->setVisible(true);
		imageLabel->adjustSize();
		zoomOut();
	}
	void Viewport::deleteImage()
	{
		imageLabel->clear();
	}
	/**************************************************************************/
	/*
		 \brief image zoom in
	*/
	/**************************************************************************/
	void Viewport::zoomIn()
	{
		scaleImage(1.25);
	}
	/**************************************************************************/
	/*
		 \brief image zoom out
	*/
	/**************************************************************************/
	void Viewport::zoomOut()
	{
		scaleImage(0.8);
	}
	/**************************************************************************/
	/*
		 \brief reset image zoom
	*/
	/**************************************************************************/
	void Viewport::normalSize()
	{
		imageLabel->adjustSize();
		scaleFactor = 1.0;
	}
	/**************************************************************************/
	/*
		 \brief fit image to window
	*/
	/**************************************************************************/
	void Viewport::fitToWindow()
	{
		normalSize();
	}
	/**************************************************************************/
	/*
		 \brief viewport actions
	*/
	/**************************************************************************/
	void Viewport::AddActions(QMenu* menu)
	{
		zoomInAct = menu->addAction
		(tr("Zoom &In (25%)"), this, &Viewport::zoomIn);
		zoomInAct->setShortcut(QKeySequence::ZoomIn);
		zoomInAct->setEnabled(true);

		zoomOutAct = menu->addAction
		(tr("Zoom &Out (25%)"), this, &Viewport::zoomOut);
		zoomOutAct->setShortcut(QKeySequence::ZoomOut);
		zoomOutAct->setEnabled(true);

		normalSizeAct = menu->addAction
		(tr("&Normal Size"), this, &Viewport::normalSize);
		normalSizeAct->setShortcut(tr("Ctrl+S"));
		normalSizeAct->setEnabled(true);

		menu->addSeparator();

		fitToWindowAct = menu->addAction
		(tr("&Fit to Window"), this, &Viewport::fitToWindow);
		fitToWindowAct->setEnabled(true);
		fitToWindowAct->setCheckable(true);
		fitToWindowAct->setShortcut(tr("Ctrl+F"));
	}

	/**************************************************************************/
	/*
		 \brief image scaling
	*/
	/**************************************************************************/
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