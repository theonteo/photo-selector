/*****************************************************************************/
/*!
\file ImageCheckBox.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/
#ifndef IMAGECHECKBOX_H
#define IMAGECHECKBOX_H

#include <QCheckBox>
#include <QWidget>
#include <qstring.h>
#include <functional>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class ImageCheckBox : public QCheckBox
{
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
};

#endif