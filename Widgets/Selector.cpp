/*****************************************************************************/
/*!
\file Selector.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "Widgets/Selector.h"
#include "App/QDefinitions.h"
#include "Widgets/Service.h"
#include "App/PhotoSelector.h"
#include "Widgets/ImageCheckBox.h"

namespace PhotoSelector
{
	/**************************************************************************/
	/*
		 \brief constructor
	*/
	/**************************************************************************/
	Selector::Selector(){}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	void Selector::GenerateFileCheckbox()
	{
		//remove all checkboxes
		for (auto& i : checkBoxes)
			box->removeWidget(&*i.second);

		checkBoxes.clear();

		if (Data::Service<PhotoSelector>::Exist())
		{
			const auto& directories = Data::Service<PhotoSelector>::Get().
				GetFolder().GetDirectory().GetDirectoryFileNames();

			//get info from load directory
			for (size_t i = 0; i < directories.size(); ++i)
			{
				std::unique_ptr< ImageCheckBox> checkBox =
					std::make_unique< ImageCheckBox>(tr(directories[i].toStdString().c_str()));
				//	std::make_unique<QCheckBox>(tr(directories[i].toStdString().c_str()));
					//connect hover
				/*	QObject::connect(&*checkBox, SIGNAL(clicked()), this, SLOT(SizeCHange()));*/

				box->addWidget(&*checkBox);
				checkBoxes.insert({ directories[i], std::move(checkBox) });


			}
		}
	}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	void Selector::GetSelectedCheckboxes()
	{
		for (const auto& [fileName, checkbox] : checkBoxes)
		{
			if (checkbox->isChecked())
			{
				selectedImagesPath.push_back(fileName);
			}
		}
	}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	void Selector::GenerateWidgets()
	{
		box = std::make_unique< QVBoxLayout>();
		widget = std::make_unique < QWidget>();
		groupBox = std::make_unique < QGroupBox>(tr("Image Selector"));

		scrollArea = std::make_unique < QScrollArea>();
		scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
		scrollArea->setWidgetResizable(true);
		GenerateFileCheckbox();

		box->addStretch(0);
		widget->setLayout(&*box);
		scrollArea->setWidget(&*widget);

	}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	const std::unique_ptr < QGroupBox>& Selector::GetGroupBox() const
	{
		return groupBox;
	}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	const std::unique_ptr < QScrollArea>& Selector::GetScrollArea() const
	{
		return scrollArea;
	}
	/**************************************************************************/
	/*
		 \brief
	*/
	/**************************************************************************/
	const std::vector<QString>& Selector::GetImagesPath() const
	{
		return selectedImagesPath;
	}
}
