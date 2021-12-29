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
		 \brief generate checkbox widgets
	*/
	/**************************************************************************/
	void Selector::GenerateFileCheckbox()
	{
		//remove all checkboxes
		for (auto& i : checkBoxes)		
			i.second->hide();

		if (Data::Service<PhotoSelector>::Exist())
		{
			const auto& directories = Data::Service<PhotoSelector>::Get().
				GetFolder().GetDirectory().GetDirectoryFileNames();

			//get info from load directory
			for (size_t i = 0; i < directories.size(); ++i)
			{
				const auto& str = directories[i];
				
					std::unique_ptr< ImageCheckBox> checkBox =
						std::make_unique< ImageCheckBox>
						(tr(str.toStdString().c_str()));

					box->addWidget(&*checkBox);
					checkBoxes.insert({ directories[i], std::move(checkBox) });
					checkboxSet.insert(str);
					checkBoxes.find(str)->second->show();
			
			}
		}
	}
	/**************************************************************************/
	/*
		 \brief get paths which are selected by user
	*/
	/**************************************************************************/
	void Selector::GetSelectedCheckboxes()
	{
		for (const auto& [fileName, checkbox] : checkBoxes)
			if (checkbox->isChecked())
				selectedImagesPath.push_back(fileName);
	}
	/**************************************************************************/
	/*
		 \brief generate selector widgets
	*/
	/**************************************************************************/
	void Selector::GenerateWidgets()
	{
		box = std::make_unique< QVBoxLayout>();
		widget = std::make_unique < QWidget>();
		groupBox = std::make_unique < QGroupBox>(tr("Image Selector"));

		scrollArea = std::make_unique < QScrollArea>();
		scrollArea->setVerticalScrollBarPolicy
		(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
		scrollArea->setWidgetResizable(true);
		GenerateFileCheckbox();

		box->addStretch(0);
		widget->setLayout(&*box);
		scrollArea->setWidget(&*widget);
	}
	/**************************************************************************/
	/*
		 \brief return group box
	*/
	/**************************************************************************/
	const std::unique_ptr < QGroupBox>& Selector::GetGroupBox() const
	{
		return groupBox;
	}
	/**************************************************************************/
	/*
		 \brief return scroll area
	*/
	/**************************************************************************/
	const std::unique_ptr < QScrollArea>& Selector::GetScrollArea() const
	{
		return scrollArea;
	}
	/**************************************************************************/
	/*
		 \brief return all image paths
	*/
	/**************************************************************************/
	const std::vector<QString>& Selector::GetImagesPath() const
	{
		return selectedImagesPath;
	}
}
