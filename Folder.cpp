#include "Folder.h"

#include "QDefinitions.h"
#include "PhotoSelector.h"
#include "Service.h"
#include "Selector.h"

namespace Photo
{
	QGroupBox* Folder::GetGroupBox() const
	{
		return groupBox;
	}
	void Folder::GenerateWidgets()
	{
		box = new QVBoxLayout;

		groupBox = new QGroupBox(PhotoSelector::tr("Folder Selection"));
		groupBox->setFlat(true);

		QCheckBox* checkBox1 = new QCheckBox(PhotoSelector::tr("&Checkbox 1"));
		QCheckBox* checkBox2 = new QCheckBox(PhotoSelector::tr("C&heckbox 2"));
		checkBox2->setChecked(true);
		QCheckBox* tristateBox = new QCheckBox(PhotoSelector::tr("Tri-&state button"));
		tristateBox->setTristate(true);

		tristateBox->setCheckState(Qt::PartiallyChecked);

		//QLineEdit* inputFolder = new QLineEdit(PhotoSelector::tr("&Input Folder"));
		//QLineEdit* outputFolder = new QLineEdit(PhotoSelector::tr("&	Output Folder"));


		labelInput = new QLabel;
		labelInput->setText("Input Folder: None");
		QPushButton* inputButton = new QPushButton(PhotoSelector::tr("&Input Folder"));
		inputButton->setFixedSize(100, 25);
		labelOutput = new QLabel;
		labelOutput->setText("Output Folder: None");
		QPushButton* outputButton = new QPushButton(PhotoSelector::tr("&Output Folder"));
		outputButton->setFixedSize(100, 25);

		//inputFolder->setText(PhotoSelector::tr("InputFolder"));
		//outputFolder->setText(PhotoSelector::tr("OutputFolder"));

		//add all widgets to box
		box->addWidget(checkBox1);
		box->addWidget(checkBox2);
		box->addWidget(tristateBox);
		box->addWidget(labelInput);
		box->addWidget(inputButton);
		//box->addWidget(inputFolder);
		box->addWidget(labelOutput);
		box->addWidget(outputButton);
		//box->addWidget(outputFolder);

		groupBox->setLayout(box);


		//connect buttons to folder functions
		connect(inputButton, &QPushButton::clicked, this, &Folder::SetInputFolderPath);
		connect(outputButton, &QPushButton::clicked, this, &Folder::SetOutputFolderPath);
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