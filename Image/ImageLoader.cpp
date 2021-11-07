#include "Image/ImageLoader.h"

#include "App/QDefinitions.h"
#include "App/PhotoSelector.h"

namespace Photo
{
	bool ImageLoader::loadFile(const QString& fileName,  QImage& result)
	{
		QImageReader reader(fileName);
		reader.setAutoTransform(true);
		const QImage newImage = reader.read();

		if (newImage.isNull()) {
			QMessageBox::information(nullptr, QGuiApplication::applicationDisplayName(),
				Photo::PhotoSelector::tr("Cannot load %1: %2")
				.arg(QDir::toNativeSeparators(fileName), reader.errorString()));
			return false;
		}
		result = newImage;
		//viewport.setImage(newImage);
		//updateActions();
		//setWindowFilePath(fileName);


	//	const auto& image = viewport.GetImage();
		const auto& image = result;


		const QString description = image.colorSpace().isValid()
			? image.colorSpace().description() : Photo::PhotoSelector::tr("unknown");

		const QString message = 
			Photo::PhotoSelector::tr("Opened \"%1\", %2x%3, Depth: %4 (%5)")
			.arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height())
			.arg(image.depth()).arg(description);


		//statusBar()->showMessage(message);

		return true;
	}

	bool ImageLoader::saveFile(const QString& fileName,const QImage& result)
	{
		QImageWriter writer(fileName);

		const auto& image = result;

		if (!writer.write(image))
		{
			QMessageBox::information(nullptr, QGuiApplication::applicationDisplayName(),
				Photo::PhotoSelector:: tr("Cannot write %1: %2")
				.arg(QDir::toNativeSeparators(fileName), writer.errorString()));
			return false;
		}
		const QString message = Photo::PhotoSelector::tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
		//statusBar()->showMessage(message);
		return true;
	}

}