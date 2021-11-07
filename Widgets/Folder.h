#pragma once
#include <QWidget>
#include <App/LoadDirectory.h>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QGroupBox;
class QLabel;
QT_END_NAMESPACE

namespace Photo
{
	class Folder final : public QWidget
	{

		std::unique_ptr<QVBoxLayout> box{ nullptr };
		std::unique_ptr < QGroupBox> groupBox{ nullptr };

		//store inpout/output paths
		QString inputPath;
		QString outputPath;

		//folder labels
		std::unique_ptr < QLabel> labelInput{ nullptr };
		std::unique_ptr < QLabel> labelOutput{ nullptr };

		//load directory class
		LoadDirectory directory;

		//input folder dialog
		void SetInputFolderPath();

		//output folder dialog
		void SetOutputFolderPath();

		//export selected images
		void ExportImages();

	public:

		//return read string
		const QString& GetInputPath() const;
		const QString& GetOutputPath() const;

		const LoadDirectory& GetDirectory() const;

		const std::unique_ptr <QGroupBox>& GetGroupBox() const;

		void GenerateWidgets();
	};
}

