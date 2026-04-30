#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Backend backend;

    // ← CETTE LIGNE doit être AVANT engine.load
    engine.rootContext()->setContextProperty("Backend", &backend);

    engine.load(QUrl(QStringLiteral("qrc:/monapp/main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;
    return app.exec();
}
