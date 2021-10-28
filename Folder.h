#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QGroupBox;
QT_END_NAMESPACE

namespace Photo
{
	class Folder final : public QWidget
	{
		QVBoxLayout* box{ nullptr };
		QGroupBox* groupBox{ nullptr };

		//store inpout/output paths
		QString inputPath;
		QString outputPath;


		//input folder dialog
		void SetInputFolderPath();

		//output folder dialog
		void SetOutputFolderPath();

	public:

		//return read string
		const QString& GetInputPath() const;
		const QString& GetOutputPath() const;

		QGroupBox* GetGroupBox() const;

		void GenerateWidgets();
	};
}

