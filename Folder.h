#pragma once
#include "Widget.h"

namespace Photo
{

	class Folder final : public Widget
	{

	public:
		std::vector<QWidget*>& GetWidgets() override;
		void GenerateWidgets() override;
	};
}

