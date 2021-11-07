/*****************************************************************************/
/*!
\file Folder.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "Widgets/Folder.h"
#include "App/QDefinitions.h"
#include "App/PhotoSelector.h"
#include "Widgets/Service.h"
#include "Widgets/Selector.h"
#include <iostream>

namespace PhotoSelector
{
	/**************************************************************************/
	/*
		 \brief create main folder widget
	*/
	/**************************************************************************/
	void Folder::GenerateWidgets()
	{
		box = std::make_unique< QVBoxLayout>();
		groupBox = std::make_unique < QGroupBox>
			(PhotoSelector::tr("Folder Selection"));
		groupBox->setFlat(true);

		labelInput = std::make_unique < QLabel>();
		labelInput->setText("Input Folder: None");

		QPushButton* inputButton = 
			new QPushButton(PhotoSelector::tr("&Input Folder"));

		inputButton->setFixedSize(100, 25);
		labelOutput = std::make_unique < QLabel>();
		labelOutput->setText("Output Folder: None");

		QPushButton* outputButton = 
			new QPushButton(PhotoSelector::tr("&Output Folder"));
		outputButton->setFixedSize(100, 25);

		QPushButton* exportButton =
			new QPushButton(PhotoSelector::tr("&Export Selected Images"));

		box->addWidget(&*labelInput);
		box->addWidget(inputButton);
		box->addWidget(&*labelOutput);
		box->addWidget(outputButton);
		box->addWidget(exportButton);

		groupBox->setLayout(&*box);

		//connect buttons to folder functions
		connect(inputButton, &QPushButton::clicked,
			this, &Folder::SetInputFolderPath);
		connect(outputButton, &QPushButton::clicked,
			this, &Folder::SetOutputFolderPath);
		connect(exportButton, &QPushButton::clicked,
			this, &Folder::ExportImages);
	}
	/**************************************************************************/
	/*
		 \brief set path for input folder
	*/
	/**************************************************************************/
	void Folder::SetInputFolderPath()
	{

		inputPath = QFileDialog::getExistingDirectory
		(this, tr("Select Input Directory"),
			"/",
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

		labelInput->setText("Input Folder : " + inputPath);

		//generate directory iterator
		directory.GenerateDirectory(inputPath);

		auto& selector = Data::Service<PhotoSelector>::Get().GetSelector();
		selector.GenerateFileCheckbox();

	}
	/**************************************************************************/
	/*
		 \brief set path for output folder
	*/
	/**************************************************************************/
	void Folder::SetOutputFolderPath()
	{
		outputPath = QFileDialog::getExistingDirectory
		(this, tr("Select Output Directory"),
			"/",
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

		//change output label
		labelOutput->setText("Output Folder : " + outputPath);
	}
	/**************************************************************************/
	/*
		 \brief export all images to output folder
	*/
	/**************************************************************************/
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
	/**************************************************************************/
	/*
		 \brief return group box
	*/
	/**************************************************************************/
	const std::unique_ptr <QGroupBox>& Folder::GetGroupBox() const
	{
		return groupBox;
	}
	/**************************************************************************/
	/*
		 \brief return input path 
	*/
	/**************************************************************************/
	const QString& Folder::GetInputPath() const
	{
		return inputPath;
	}
	/**************************************************************************/
	/*
		 \brief return output path
	*/
	/**************************************************************************/
	const QString& Folder::GetOutputPath() const
	{
		return outputPath;
	}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	const LoadDirectory& Folder::GetDirectory() const
	{
		return directory;
	}
}