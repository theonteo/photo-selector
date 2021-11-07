#include "Widgets/Selector.h"
#include "App/QDefinitions.h"
#include "Widgets/Service.h"
#include "App/PhotoSelector.h"
#include "Widgets/ImageCheckBox.h"

namespace Photo
{
	QGroupBox* Selector::GetGroupBox() const
	{
		return groupBox;
	}

	Selector::Selector()
	{	}

	QScrollArea* Selector::GetScrollArea() const
	{
		return scrollArea;
	}

	const std::vector<QString>& Selector::GetImagesPath() const
	{
		return selectedImagesPath;
	}

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
				connect(&*checkBox, &QCheckBox::clicked, this, &Selector::ShowImageOnViewport);

				box->addWidget(&*checkBox);
				checkBoxes.insert({ directories[i], std::move(checkBox) });

				
			}
		}
	}

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
	void Selector::ShowImageOnViewport(bool ar)
	{
		const auto& photoSelector = Data::Service<PhotoSelector>::Get();
		/*photoSelector.open()
		int x = 0;*/
	}
}
