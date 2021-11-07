/*****************************************************************************/
/*!
\file ImageLoader.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>

namespace PhotoSelector
{
	class ImageLoader final : public QObject
	{
	public:
		bool loadFile
		(const QString& fileName, QImage& result);

		bool saveFile
		(const QString& fileName, const QImage& result);
	};
}

#endif