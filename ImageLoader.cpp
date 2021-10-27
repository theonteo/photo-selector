#include "ImageLoader.h"

#include "QDefinitions.h"

namespace Photo
{

	bool ImageLoader::loadFile(const QString& fileName)
	{
		QImageReader reader(fileName);
		reader.setAutoTransform(true);
		const QImage newImage = reader.read();

		if (newImage.isNull()) {
			QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
				tr("Cannot load %1: %2")
				.arg(QDir::toNativeSeparators(fileName), reader.errorString()));
			return false;
		}

		viewport.setImage(newImage);
		updateActions();
		setWindowFilePath(fileName);


		const auto& image = viewport.GetImage();

		const QString description = image.colorSpace().isValid()
			? image.colorSpace().description() : tr("unknown");

		const QString message = tr("Opened \"%1\", %2x%3, Depth: %4 (%5)")
			.arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height())
			.arg(image.depth()).arg(description);
		statusBar()->showMessage(message);

		return true;
	}

	bool  ImageLoader::saveFile(const QString& fileName)
	{
		QImageWriter writer(fileName);

		const auto& image = viewport.GetImage();




		if (!writer.write(image)) {
			QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
				tr("Cannot write %1: %2")
				.arg(QDir::toNativeSeparators(fileName), writer.errorString()));
			return false;
		}
		const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
		statusBar()->showMessage(message);
		return true;
	}

}