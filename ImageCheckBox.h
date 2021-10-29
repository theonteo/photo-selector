#pragma once

#include <QCheckBox>
#include <QWidget>
#include <qstring.h>
#include <functional>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class ImageCheckBox : public QCheckBox
{
	Q_OBJECT
		QString text;
public:

	ImageCheckBox(QWidget* parent = nullptr)
		: QCheckBox(parent) { }

	ImageCheckBox(const QString& txt, QWidget* parent = nullptr)
		: QCheckBox(parent)
	{
		text = txt;
		setText(txt);
	}
protected:

	virtual void enterEvent(QEnterEvent* ev) override;
	virtual void leaveEvent(QEvent* ev) override;
};
