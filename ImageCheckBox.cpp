#include "ImageCheckBox.h"
#include "PhotoSelector.h"
#include "Service.h"

void ImageCheckBox::enterEvent(QEnterEvent* ev)
{

	auto& app = Data::Service<Photo::PhotoSelector>().Get();
	app.open(app.GetFolder().GetInputPath() + "/" + text);
	//func();
}

void ImageCheckBox::leaveEvent(QEvent* ev)
{
}
