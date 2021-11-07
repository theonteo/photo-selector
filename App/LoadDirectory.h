/*****************************************************************************/
/*!
\file LoadDirectory.h
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#ifndef LOADDIRECTORY_H
#define LOADDIRECTORY_H

#include <QObject>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace PhotoSelector
{
	class LoadDirectory
	{
		std::vector<QString> directoryFileNames;
	public:
		const std::vector<QString>& GetDirectoryFileNames() const;
		void GenerateDirectory(const QString& directorypath);
	};
}
#endif