#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "xcodedata.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    //!Set default style for Native macOS
    {
        QQuickStyle::setStyle("macOS");
    }

    qmlRegisterType<RoleEntryModel>("XcodeDataModel", 1, 0, "XcodeDataModel");

    const QUrl url(u"qrc:/XcodeReleases/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
