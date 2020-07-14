#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "settings.h"
#include <QQuickStyle>
#include "phonenumberformatterservice.h"
#include <boost/locale.hpp>
#include "api.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterType<PhoneNumberFormatterService>("MessengerDesktop.Numbers", 1, 0, "PhoneNumberService");
    qmlRegisterType<Api>("MessengerDesktop.Backend.Api", 1, 0, "Api");

    //QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    Settings s;

    QQmlApplicationEngine engine;
    const QUrl url(s.is_logged_in() ? QStringLiteral("qrc:/main/MainWindow.qml") : QStringLiteral("qrc:/auth/AuthWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            qDebug("Object uninitialized, probably error in qUrl: %s", url.url().toStdString().c_str());
//            QCoreApplication::exit(-1);
   }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

