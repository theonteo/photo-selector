#include "App/LoadDirectory.h"

#include <filesystem>
#include <qstring.h>

namespace Photo
{
	void LoadDirectory::GenerateDirectory(const QString& directorypath)
	{
		std::string ext(".jpg");

		const auto& str = directorypath.toStdString();
		for (const auto& entry : std::filesystem::directory_iterator(str))
		{
			const auto& path = entry.path();
			if (path.extension() == ext)
			{
				directoryFileNames.emplace_back
				(QString(path.filename().string().c_str()));
			}
		}
	}

	const std::vector<QString>& LoadDirectory::GetDirectoryFileNames() const
	{
		return directoryFileNames;
	}
}
