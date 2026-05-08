#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "Backend.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");  // style Qt

    Backend backend;

    QQmlApplicationEngine engine;

    // exposer C++ à QML
    engine.rootContext()->setContextProperty("Backend", &backend);

    engine.load(QUrl(QStringLiteral("qrc:/monapp/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
