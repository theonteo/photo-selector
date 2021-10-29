#include "Selector.h"
#include "QDefinitions.h"
#include "Service.h"
#include "PhotoSelector.h"

namespace Photo
{
	QGroupBox* Selector::GetGroupBox() const
	{
		return groupBox;
	}

	Selector::Selector()
	{
	}

	QScrollArea* Selector::GetScrollArea() const
	{
		return scrollArea;
	}

	void Selector::GenerateFileCheckbox()
	{
	
		for (auto& i : checkBoxes)
		{
			box->removeWidget(&*i);

		}
		checkBoxes.clear();

		for (size_t i = 0; i < 100; ++i)
		{
			std::unique_ptr< QCheckBox> checkBox = std::make_unique< QCheckBox>(tr("iu"));
			box->addWidget(&*checkBox);
			checkBoxes.emplace_back(std::move(checkBox));
		}
		if (Data::Service<PhotoSelector>::Exist())
		{
			const auto& directories = Data::Service<PhotoSelector>::Get().
				GetFolder().GetDirectory().GetDirectoryFileNames();
			//get info from load directory
			for (size_t i = 0; i <100; ++i)
			{
				std::unique_ptr< QCheckBox> checkBox = std::make_unique< QCheckBox>(tr("iu"));
				box->addWidget(&*checkBox);
				checkBoxes.emplace_back(std::move(checkBox));
			}
		}
	//	scrollArea->adjustSize();
	}

	void Selector::GenerateWidgets()
	{
		box = new QVBoxLayout;
		widget = new QWidget;

		groupBox = new QGroupBox(tr("Image Selector"));
		//groupBox->setFlat(true);

		scrollArea = new QScrollArea;
		scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
		scrollArea->setWidgetResizable(true);
		GenerateFileCheckbox();

		box->addStretch(0);
		widget->setLayout(box);
		scrollArea->setWidget(widget);



		//groupBox->setLayout(box);


	}
}
