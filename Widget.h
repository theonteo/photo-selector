#pragma once
#include <QObject>
#include <vector>



class Widget :public QObject
{
	Q_OBJECT;
protected:
	std::vector<QWidget*> widgets;

public:
	virtual const std::vector<QWidget*>&  GetWidgets() = 0;
	virtual void GenerateWidgets() = 0;
};