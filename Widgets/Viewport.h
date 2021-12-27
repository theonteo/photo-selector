/*****************************************************************************/
/*!
\file Viewport.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QImage>
#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QGroupBox;
class QMenu;
class QWidget;
class QObject;
QT_END_NAMESPACE

namespace PhotoSelector
{
	class Viewport :public QObject
	{
	private:
		//main image
		QImage image;

		std::unique_ptr <QLabel> imageLabel{ nullptr };
		std::unique_ptr <QScrollArea> scrollArea{ nullptr };
		std::unique_ptr <QWidget> widget{ nullptr };

		QAction* zoomInAct{ nullptr };
		QAction* zoomOutAct{ nullptr };
		QAction* normalSizeAct{ nullptr };
		QAction* fitToWindowAct{ nullptr };

		//image scale value
		double scaleFactor{ 1 };

	public:
		Viewport();

		void CreateViewportWidget();

		//get reference of image label
		const  std::unique_ptr < QLabel>& GetImageLabel() const;

		//get reference of image
		const QImage& GetImage() const;
		QImage& GetImage();

		//image functions
		void setImage(const QImage& newImage);
		void deleteImage();
		void adjustScrollBar(QScrollBar* scrollBar, double factor);

		const std::unique_ptr <QWidget>& GetViewportWidget() const;
		const std::unique_ptr <QScrollArea>& GetScrollArea() const;

		//scaling functions
		void scaleImage(double factor);

	private slots:
		void zoomIn();
		void zoomOut();
		void normalSize();
		void fitToWindow();
	private:
		void AddActions(QMenu* menu);
	};
}

#endif