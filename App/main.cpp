/*****************************************************************************/
/*!
\file main.cpp
\author Theon Teo
\par email: theonteo96@gmail.com
\date 2021
\brief
This project contains simple qt application
\Not for distribution
*/
/*****************************************************************************/

#include <QApplication>
#include <QCommandLineParser>
#include "App/QDefinitions.h"
#include "App/PhotoSelector.h"
#include "Widgets/Service.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(PhotoSelector::PhotoSelector::tr("Photo Selector"));
    QCommandLineParser commandLineParser;

    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument
    (PhotoSelector::PhotoSelector::tr("[file]"),
      PhotoSelector::PhotoSelector::tr("Image file to open."));

    commandLineParser.process(QCoreApplication::arguments());
    
    Data::Service< PhotoSelector::PhotoSelector>::Register();

    auto& photoSelector =
      Data::Service<PhotoSelector::PhotoSelector>::Get();

    if (!commandLineParser.positionalArguments().isEmpty()) return -1;
    
    photoSelector.show();

    int err = app.exec();
    Data::Service< PhotoSelector::PhotoSelector>::Release();

    return err;
}
