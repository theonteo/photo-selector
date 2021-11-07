/*****************************************************************************/
/*!
\file Selector.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#ifndef SELECTOR_H
#define SELECTOR_H
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
namespace PhotoSelector
{
	class Selector final : public QWidget
	{
		//selector widgets
		std::unique_ptr <QVBoxLayout> box{ nullptr };
		std::unique_ptr <QGroupBox> groupBox{ nullptr };
		std::unique_ptr <QScrollArea> scrollArea{ nullptr };
		std::unique_ptr <QWidget> widget{ nullptr };

	public:
		Selector();

		//stores all checkbox widgets
		std::map<QString, std::unique_ptr<ImageCheckBox>> checkBoxes;
		std::vector<QString> selectedImagesPath;

		//getters
		const std::unique_ptr < QGroupBox>& GetGroupBox() const;
		const std::unique_ptr < QScrollArea>& GetScrollArea() const;
		const std::vector<QString>& GetImagesPath() const;

		void GenerateFileCheckbox();
		void GetSelectedCheckboxes();
		void GenerateWidgets();
	};
}

#endif