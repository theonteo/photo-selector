#pragma once
#include <QObject>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace Photo
{
	class LoadDirectory
	{
		std::vector<QString> directoryFileNames;

	public:

		const std::vector<QString>& GetDirectoryFileNames() const;
		void GenerateDirectory(const QString& directorypath);
	};
}
