#pragma once
#include <QWidget>
#include <map>

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
		QGroupBox* GetGroupBox() const;
		QScrollArea* GetScrollArea() const;

		void GenerateFileCheckbox();

		void GetSelectedCheckboxes();
		void GenerateWidgets();
	};
}

