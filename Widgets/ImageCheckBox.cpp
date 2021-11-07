/*****************************************************************************/
/*!
\file ImageCheckBox.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "App/QDefinitions.h"
#include "Widgets/ImageCheckBox.h"
#include "App/PhotoSelector.h"
#include "Widgets/Service.h"

/**************************************************************************/
/*
	 \brief widget enter event
*/
/**************************************************************************/
void ImageCheckBox::enterEvent(QEnterEvent* ev)
{
	(void)ev;
	auto& app = Data::Service<PhotoSelector::PhotoSelector>().Get();
	app.open(app.GetFolder().GetInputPath() + "/" + text);
}
