
#include <QApplication>
#include <QCommandLineParser>

#include "PhotoSelector.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(Photo::PhotoSelector::tr("Image Viewer"));
    QCommandLineParser commandLineParser;

    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(Photo::PhotoSelector::tr("[file]"), Photo::PhotoSelector::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());

    Photo::PhotoSelector imageViewer;
    if (!commandLineParser.positionalArguments().isEmpty()) {
        return -1;
    }
    imageViewer.show();
    return app.exec();
}
