#pragma once
#include <QObject>
namespace Photo
{
	class ImageLoader : public QObject
	{
		Q_OBJECT
	public:
		bool loadFile(const QString& fileName, QImage& result);
		bool saveFile(const QString& fileName, const QImage& result);
	};


}