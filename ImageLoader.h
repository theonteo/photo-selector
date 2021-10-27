#pragma once
#include <QObject>
namespace Photo
{
	class ImageLoader
	{
	public:
		bool loadFile(const QString& fileName);
		bool saveFile(const QString& fileName);
	};


}