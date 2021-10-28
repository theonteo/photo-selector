#include "Folder.h"

#include "QDefinitions.h"
#include "PhotoSelector.h"

namespace Photo
{
	void Folder::GenerateWidgets()
	{
		QGroupBox* groupBox = new QGroupBox(PhotoSelector::tr("Folder Selection"));
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

		widgets.emplace_back(checkBox1);
		widgets.emplace_back(checkBox2);
		widgets.emplace_back(tristateBox);
		widgets.emplace_back(labelInput);
		widgets.emplace_back(inputButton);
		widgets.emplace_back(inputFolder);
		widgets.emplace_back(labelOutput);
		widgets.emplace_back(outputButton);
		widgets.emplace_back(outputFolder);




		//TODO
		//connect buttons to folder functions
		//connect(openCoverArt, &QPushButton::clicked, this, &MetaDataDialog::openCoverArtImage);

	}
	std::vector<QWidget*>& Folder::GetWidgets()
	{
		return widgets;
	}
}