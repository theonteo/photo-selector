#include "Widgets/Folder.h"

#include "App/QDefinitions.h"
#include "App/PhotoSelector.h"
#include "Widgets/Service.h"
#include "Widgets/Selector.h"
#include <iostream>

namespace Photo
{
	const std::unique_ptr <QGroupBox>& Folder::GetGroupBox() const
	{
		return groupBox;
	}
	void Folder::GenerateWidgets()
	{
		box = std::make_unique< QVBoxLayout>();

		groupBox = std::make_unique < QGroupBox>(PhotoSelector::tr("Folder Selection"));
		groupBox->setFlat(true);

		//QCheckBox* checkBox1 = new QCheckBox(PhotoSelector::tr("&Checkbox 1"));
		//QCheckBox* checkBox2 = new QCheckBox(PhotoSelector::tr("C&heckbox 2"));
		/*checkBox2->setChecked(true);
		QCheckBox* tristateBox = new QCheckBox(PhotoSelector::tr("Tri-&state button"));
		tristateBox->setTristate(true);

		tristateBox->setCheckState(Qt::PartiallyChecked);*/

		//QLineEdit* inputFolder = new QLineEdit(PhotoSelector::tr("&Input Folder"));
		labelInput = std::make_unique < QLabel>();
		labelInput->setText("Input Folder: None");

		QPushButton* inputButton = new QPushButton(PhotoSelector::tr("&Input Folder"));
		inputButton->setFixedSize(100, 25);
		labelOutput = std::make_unique < QLabel>();
		labelOutput->setText("Output Folder: None");
		QPushButton* outputButton = new QPushButton(PhotoSelector::tr("&Output Folder"));
		outputButton->setFixedSize(100, 25);

		QPushButton* exportButton =
			new QPushButton(PhotoSelector::tr("&Export Selected Images"));

		//add all widgets to box
	/*	box->addWidget(checkBox1);
		box->addWidget(checkBox2);
		box->addWidget(tristateBox);*/
		box->addWidget(&*labelInput);
		box->addWidget(inputButton);

		box->addWidget(&*labelOutput);
		box->addWidget(outputButton);

		box->addWidget(exportButton);

		groupBox->setLayout(&*box);

		//connect buttons to folder functions
		connect(inputButton, &QPushButton::clicked, this, &Folder::SetInputFolderPath);
		connect(outputButton, &QPushButton::clicked, this, &Folder::SetOutputFolderPath);
		connect(exportButton, &QPushButton::clicked, this, &Folder::ExportImages);
	}
	void Folder::SetInputFolderPath()
	{

		inputPath = QFileDialog::getExistingDirectory(this, tr("Select Input Directory"),
			"/",
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);


		labelInput->setText("Input Folder : " + inputPath);

		//QString fileName = dialog.getSaveFileName(this,
		//	tr("Select input folder"), QDir::currentPath(), tr(""));


		//generate directory iterator
		directory.GenerateDirectory(inputPath);

		//const auto& allFiles = directory.GetDirectoryFileNames();

		auto& selector = Data::Service<PhotoSelector>::Get().GetSelector();
		selector.GenerateFileCheckbox();

	}
	void Folder::SetOutputFolderPath()
	{
		outputPath = QFileDialog::getExistingDirectory(this, tr("Select Output Directory"),
			"/",
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

		//change output label
		labelOutput->setText("Output Folder : " + outputPath);
	}

	void Folder::ExportImages()
	{

		auto& selector =
			Data::Service<PhotoSelector>::Get().GetSelector();

		//generated selected paths to export
		selector.GetSelectedCheckboxes();
		try
		{
			//copy files from path to path
			for (const auto& i : selector.GetImagesPath())
			{
				const auto& filePath = (inputPath + "/" + i).toStdString();
				const auto& fileExportPath = (outputPath + "/" + i).toStdString();

				if (!std::filesystem::exists(fileExportPath))
					std::filesystem::copy_file(filePath, fileExportPath);
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	const QString& Folder::GetInputPath() const
	{
		return inputPath;
	}

	const QString& Folder::GetOutputPath() const
	{
		return outputPath;
	}
	const LoadDirectory& Folder::GetDirectory() const
	{
		return directory;
	}
}