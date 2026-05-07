#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include "Backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");  // ← forcer le style clair

    Backend backend;

    QQmlApplicationEngine engine;
    // ← CETTE LIGNE doit être AVANT engine.load
    engine.rootContext()->setContextProperty("Backend", &backend);

    engine.load(QUrl(QStringLiteral("qrc:/monapp/main.qml")));

    if (engine.rootObjects().isEmpty()) return -1;
    return app.exec();
}
