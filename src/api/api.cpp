#include "api.h"

Api::Api(QObject *parent) : QObject(parent) {
    this->_manager = new QNetworkAccessManager(this);
    connect(this->_manager, &QNetworkAccessManager::finished, this, &Api::handle_response);
}
Promise* Api::get_server_preferences() {
    auto p = new Promise {this, api_url(QStringLiteral("/getConnPrefs")), [](QNetworkReply* reply) -> QVariant {

            if (auto err = reply->error())
                return err;

            QJsonParseError err;
            auto jdoc = QJsonDocument::fromJson(reply->readAll(), &err);
            if (jdoc.isNull()) {
                qDebug() << "Error parsing /getConnPrefs answer; error: " << err.errorString() << "; at: " << err.offset;
                return QNetworkReply::ProtocolFailure;
            }

            auto json = jdoc.object();
            if (
                json.contains(QStringLiteral("realTimeServerIPv4"))
                    && json[QStringLiteral("realTimeServerIpv4")].isString() &&
                json.contains(QStringLiteral("realTimeServerIPv6"))
                    && json[QStringLiteral("realTimeServerIpv6")].isString() &&
                json.contains(QStringLiteral("realTimePortIPv4"))
                    && json[QStringLiteral("realTimePortIPv4")].isDouble() &&
                json.contains(QStringLiteral("realTimePortIPv6"))
                    && json[QStringLiteral("realTimePortIPv6")].isDouble()
                )
                return json.toVariantMap();
             else {
                qDebug() << "Error parsing /getConnPrefs answer; could not verify all fields";
                return QNetworkReply::ProtocolFailure;
            }
        }};
    handles.append(p);
    return p;
}

void Api::handle_response(QNetworkReply *res) {
    QObject* orig = res->request().originatingObject();
    if (typeid(Promise) != typeid (orig)) {
        qDebug() << "unwanted request, originating object " << typeid (orig).name();
        return;
    }
    auto i = handles.lastIndexOf(dynamic_cast<Promise*>(const_cast<QObject*>(orig)));
    if (i == -1) {
        qDebug() << "pointer to Promise not found in handles list";
        return;
    }
    auto promise = handles[i];
    promise->handle_response(res);
    handles.removeAt(i);
    delete promise;
    res->deleteLater();
}

const QString Api::path_prefix = QStringLiteral("/api");

void Api::set_base_url(QString url) {
    this->base_url = url;
}
QString Api::get_base_url() {
    return this->base_url;
}
QUrl Api::api_url(QString path) {
    return QUrl(base_url + path_prefix + path);
}
