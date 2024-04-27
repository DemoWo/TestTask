#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    MainWindow *mainwindow = new MainWindow(&app);
    engine.rootContext()->setContextProperty("_mainwindow", mainwindow);
    const QUrl url(QStringLiteral("qrc:/test/main.qml"));
    mainwindow->Init();
    QQuickStyle::setStyle( "Basic" );   // Нужно для правильного внешнего вида GroupBox, ScrollView и т.д.
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
