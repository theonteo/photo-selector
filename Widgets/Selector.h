#pragma once
#include <QWidget>
#include <map>
#include <vector>
#include "Widgets/ImageCheckBox.h"

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
		std::unique_ptr <QVBoxLayout> box{ nullptr };
		std::unique_ptr <QGroupBox> groupBox{ nullptr };
		std::unique_ptr <QScrollArea> scrollArea{ nullptr };
		std::unique_ptr <QWidget> widget{ nullptr };

	public:
		Selector();

		std::map<QString, std::unique_ptr<ImageCheckBox>> checkBoxes;
		std::vector<QString> selectedImagesPath;

		const std::unique_ptr < QGroupBox>& GetGroupBox() const;
		const std::unique_ptr < QScrollArea>& GetScrollArea() const;

		const std::vector<QString>& GetImagesPath() const;

		void GenerateFileCheckbox();

		void GetSelectedCheckboxes();
		void GenerateWidgets();

		void ShowImageOnViewport(bool ar);
	};
}

