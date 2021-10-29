#pragma once
#include <QWidget>
#include <map>
#include <vector>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QGroupBox;
class QScrollArea;
class QWidget;
class QCheckBox;
QT_END_NAMESPACE

namespace Photo
{
	class Selector final : public QWidget
	{
		QVBoxLayout* box{ nullptr };
		QGroupBox* groupBox{ nullptr };
		QScrollArea* scrollArea{ nullptr };
		QWidget* widget{ nullptr };

	public:
		Selector();

		std::map<QString,std::unique_ptr<QCheckBox>> checkBoxes;
		std::vector<QString> selectedImagesPath;

		QGroupBox* GetGroupBox() const;
		QScrollArea* GetScrollArea() const;

		const std::vector<QString>& GetImagesPath() const;

		void GenerateFileCheckbox();

		void GetSelectedCheckboxes();
		void GenerateWidgets();
	};
}

