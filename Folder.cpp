#include "Folder.h"

#include "QDefinitions.h"
#include "PhotoSelector.h"
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

		QLineEdit* inputFolder = new QLineEdit(PhotoSelector::tr("&Input Folder"));
		QLineEdit* outputFolder = new QLineEdit(PhotoSelector::tr("&	Output Folder"));


		QLabel* labelInput = new QLabel;
		labelInput->setText("Input Folder");
		QPushButton* inputButton = new QPushButton(PhotoSelector::tr("&Input Folder"));
		inputButton->setFixedSize(100, 25);
		QLabel* labelOutput = new QLabel;
		labelOutput->setText("Output Folder");
		QPushButton* outputButton = new QPushButton(PhotoSelector::tr("&Output Folder"));
		outputButton->setFixedSize(100, 25);
		inputFolder->setText(PhotoSelector::tr("InputFolder"));
		outputFolder->setText(PhotoSelector::tr("OutputFolder"));


		box->addWidget(checkBox1);
		box->addWidget(checkBox2);
		box->addWidget(tristateBox);
		box->addWidget(labelInput);
		box->addWidget(inputButton);
		box->addWidget(inputFolder);
		box->addWidget(labelOutput);
		box->addWidget(outputButton);
		box->addWidget(outputFolder);

		groupBox->setLayout(box);


		//TODO
		//connect buttons to folder functions
		connect(inputButton, &QPushButton::clicked, this, &Folder::SetInputFolderPath);

	}
	void Folder::SetInputFolderPath()
	{
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"));
	}
	void Folder::SetOutputFolderPath()
	{

	}

}