#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "data/settings.h"
#include <QQuickStyle>
#include "misc/phonenumberformatterservice.h"
#include <boost/locale.hpp>
#include <QQmlContext>
#include "api/api.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QScopedPointer<Settings> s(new Settings);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<PhoneNumberFormatterService>("Misc.Numbers", 1, 0,
            "PhoneNumberService");
    qmlRegisterType<Promise>("Api", 1, 0, "Promise");
    qmlRegisterSingletonType<Api>("Api", 1, 0, "Api",
            [](QQmlEngine *, QJSEngine *e) { return new Api(e); });
    qmlRegisterSingletonInstance("Persist", 1, 0, "Settings", s.get());
    qmlRegisterUncreatableType<QNetworkReply>("Network", 1, 0,
            "NetworkReply", "Only used for NetworkReplyError enum");

//    //QQuickStyle::setStyle("Material");
//    engine.rootContext()->setContextProperty("isLoggedIn", s->is_logged_in());
//
    const QUrl url(s->is_logged_in() ? "qrc:/chat/ChatWindow.qml" : "qrc:/intro/IntroWindow.qml");
    engine.load(url);

    return QGuiApplication::exec();
}

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//                Q_UNUSED(obj)
//                Q_UNUSED(objUrl)
//        if (!obj && url == objUrl)
//            qDebug() << "Object uninitialized, probably error in qUrl: " << url.url();
//            QCoreApplication::exit(-1);
//            }, Qt::QueuedConnection);