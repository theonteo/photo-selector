/*****************************************************************************/
/*!
\file LoadDirectory.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include "App/LoadDirectory.h"

#include <filesystem>
#include <qstring.h>

namespace PhotoSelector
{
	/**************************************************************************/
	/*
		 \brief generate all image paths from directory
	*/
	/**************************************************************************/
	void LoadDirectory::GenerateDirectory(const QString& directorypath)
	{
		//currently only support jpg
		std::string ext(".jpg");
		directoryFileNames.clear();
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
	/**************************************************************************/
	/*
		 \brief return file names
	*/
	/**************************************************************************/
	const std::vector<QString>& LoadDirectory::GetDirectoryFileNames() const
	{
		return directoryFileNames;
	}
}
