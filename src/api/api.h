#pragma once

#include <QObject>
#include <exception>
#include <QNetworkAccessManager>
#include "../misc/promise.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class Api : public QObject
{
    Q_OBJECT
public:
    enum class CodeVerificationChannel {
        SMS,
        Call
    };
    Q_ENUM(CodeVerificationChannel)
    explicit Api(QObject *parent = nullptr);
    Api(QJSEngine* qjsEnginePtr);
    Q_INVOKABLE void setBaseUrl(QString url);
    Q_INVOKABLE QString getBaseUrl();

    void handle_response(QNetworkReply* res);

    Q_INVOKABLE [[maybe_unused]] Promise* getServerPrefs();
    Q_INVOKABLE [[maybe_unused]] Promise* sendCode(const QString&, CodeVerificationChannel);
    Q_INVOKABLE [[maybe_unused]] Promise* verifyCode(const QString& code, const QString& number);

    QNetworkAccessManager* _manager;

private:
    static QString getApiChannelValue(CodeVerificationChannel);
    static void normalizeNumber(QString*);
    static const QString path_prefix; // = "/api"
    static const QString protocol; // = "http://"
    QString base_url;
    QUrl api_url(const QString& path);
    QList<Promise*> handles;
    QJSEngine* engine;
signals:
};
