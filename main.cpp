
#include <QApplication>
#include <QCommandLineParser>

#include "PhotoSelector.h"
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(Photo::PhotoSelector::tr("Image Viewer"));
    QCommandLineParser commandLineParser;

    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(Photo::PhotoSelector::tr("[file]"), Photo::PhotoSelector::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());
    
    Data::Service< Photo::PhotoSelector>::Register();

    auto& photoSelector =
      Data::Service< Photo::PhotoSelector>::Get();

    if (!commandLineParser.positionalArguments().isEmpty()) return -1;
    
    photoSelector.show();

    int err = app.exec();
    Data::Service< Photo::PhotoSelector>::Release();

    return err;
}
