#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "api.h"

#include <utility>
#include <iostream>

Api::Api(QObject *parent) : QObject(parent) {
    this->_manager = new QNetworkAccessManager(this);
    connect(this->_manager, &QNetworkAccessManager::finished, this, &Api::handle_response);
}

Api::Api(QJSEngine *qjsEnginePtr) :
        QObject(nullptr), engine(qjsEnginePtr), _manager(new QNetworkAccessManager(this)) {
    connect(this->_manager, &QNetworkAccessManager::finished, this, &Api::handle_response);
}

[[maybe_unused]] Promise *Api::getServerPrefs() {
    auto p = new Promise{ [](QNetworkReply *reply) -> QVariant {

        if (auto err = reply->error())
            return err;

        QJsonParseError err{};
        auto jdoc = QJsonDocument::fromJson(reply->readAll(), &err);
        if (jdoc.isNull()) {
            qDebug() << "Error parsing /getConnPrefs answer; error: " << err.errorString() << "; at: " << err.offset;
            return QNetworkReply::ProtocolFailure;
        }

        auto json = jdoc.object();
        if (
                json.contains("realTimeServerIPv4") && json["realTimeServerIPv4"].isString() &&
                json.contains("realTimeServerIPv6") && json["realTimeServerIPv6"].isString() &&
                json.contains("realTimePortIPv4") && json["realTimePortIPv4"].isDouble() &&
                json.contains("realTimePortIPv6") && json["realTimePortIPv6"].isDouble()
                )
            return json.toVariantMap();

        qDebug() << "Error parsing /getConnPrefs answer; could not verify all fields";
        return QNetworkReply::ProtocolFailure;

    }, engine, this};
    auto req = QNetworkRequest{api_url("/getConnPrefs")};
    req.setOriginatingObject(p);
    _manager->get(req);
    handles.append(p);
    return p;
}

[[maybe_unused]] Promise* Api::sendCode(QString number, CodeVerificationChannel chan) {
    auto p = new Promise { [](QNetworkReply *reply) -> QVariant {
        if (auto err = reply->error())
            return err;
        auto code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (code.isValid())
            switch (code.toInt()) {
            case 200: return QNetworkReply::NoError;
            case 403: return QNetworkReply::AuthenticationRequiredError;
            case 400: return QNetworkReply::ContentAccessDenied;
            default: return QNetworkReply::UnknownContentError;
            }
        else return QNetworkReply::UnknownContentError;
    }, engine, this};
    auto req = QNetworkRequest {api_url("/auth/sendCode")};
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    req.setOriginatingObject(p);
    QJsonObject json{};
    json["number"] = normalizeNumber(number);
    json["channel"] = getApiChannelValue(chan);
    _manager->post(req, QJsonDocument(json).toJson(QJsonDocument::Compact));
    handles.append(p);
    return p;
}

[[maybe_unused]] Promise* Api::verifyCode(const QString &code, QString number) {
    auto p = new Promise { [](QNetworkReply *reply) -> QVariant {
        if (auto err = reply->error())
            return err;
        return reply->readAll();
    }, engine, this};
    auto req = QNetworkRequest {api_url("/auth/verifyCode")};
    req.setOriginatingObject(p);
    req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    QJsonObject json{};
    json["number"] = normalizeNumber(number);
    json["code"] = code;
    _manager->post(req, QJsonDocument {json}.toJson(QJsonDocument::Compact));
    handles.append(p);
    return p;
}

void Api::handle_response(QNetworkReply *res) {
    QObject *orig = res->request().originatingObject();
    if (auto promise = dynamic_cast<Promise *>(orig)) {
        if (!handles.contains(promise)) {
            qDebug() << "pointer to Promise not found in handles list";
            return;
        }
        promise->handle_response(res);
        handles.removeAll(promise);
        delete promise;
        res->deleteLater();
    } else qDebug() << "unwanted request, originating object " << typeid(orig).name();
}

const QString Api::path_prefix = "/api";
const QString Api::protocol = "http://";

void Api::setBaseUrl(QString url) {
    this->base_url = std::move(url);
}

QString Api::getBaseUrl() {
    return this->base_url;
}

QUrl Api::api_url(const QString& path) {
    return QUrl(protocol + base_url + path_prefix + path);
}

QString Api::getApiChannelValue(Api::CodeVerificationChannel chan) {
    switch (chan) {
        case CodeVerificationChannel::SMS:
            return "sms";
        case CodeVerificationChannel::Call:
            return "call";
    }
    return "sms";
}

QString& Api::normalizeNumber(QString& num) {
    num.replace(" ", "");
    num.replace("-", "");
    return num;
}

Promise *
Api::registerUser(const QString &token, const QString &firstName, const QString &lastName, const QString &username) {
    return nullptr; //TODO
}

#pragma clang diagnostic pop