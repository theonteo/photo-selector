/*****************************************************************************/
/*!
\file ImageLoader.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "Image/ImageLoader.h"
#include "App/QDefinitions.h"
#include "App/PhotoSelector.h"

namespace PhotoSelector
{
	/**************************************************************************/
	/*
		 \brief load an image
	*/
	/**************************************************************************/
	bool ImageLoader::loadFile(const QString& fileName,  QImage& result)
	{
		QImageReader reader(fileName);
		reader.setAutoTransform(true);
		const QImage newImage = reader.read();

		if (newImage.isNull())
		{
			QMessageBox::information
			(nullptr, QGuiApplication::applicationDisplayName(),
				PhotoSelector::PhotoSelector::tr("Cannot load %1: %2")
				.arg(QDir::toNativeSeparators(fileName), reader.errorString()));
			return false;
		}
		result = newImage;
		const auto& image = result;
		const QString description = image.colorSpace().isValid()
			? image.colorSpace().description() :
			PhotoSelector::PhotoSelector::tr("unknown");

		const QString message = 
			PhotoSelector::PhotoSelector::tr
			("Opened \"%1\", %2x%3, Depth: %4 (%5)")
			.arg(QDir::toNativeSeparators
			(fileName)).arg(image.width()).arg(image.height())
			.arg(image.depth()).arg(description);

		//statusBar()->showMessage(message);
		return true;
	}
	/**************************************************************************/
	/*
		 \brief save an image
	*/
	/**************************************************************************/
	bool ImageLoader::saveFile(const QString& fileName,const QImage& result)
	{
		QImageWriter writer(fileName);

		const auto& image = result;

		if (!writer.write(image))
		{
			QMessageBox::information
			(nullptr, QGuiApplication::applicationDisplayName(),
				PhotoSelector::PhotoSelector:: tr("Cannot write %1: %2")
				.arg(QDir::toNativeSeparators(fileName), writer.errorString()));
			return false;
		}
		const QString message = PhotoSelector::PhotoSelector::tr
		("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
		//statusBar()->showMessage(message);
		return true;
	}
}