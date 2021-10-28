#pragma once
#include <QWidget>



QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QGroupBox;
QT_END_NAMESPACE


namespace Photo
{
	class Folder final : public QWidget
	{
		QVBoxLayout* box{ nullptr };
		QGroupBox* groupBox{ nullptr };

		//input folder dialog
		void SetInputFolderPath();

		//output folder dialog
		void SetOutputFolderPath();

	public:
		QGroupBox* GetGroupBox() const;

		void GenerateWidgets();
	};
}

