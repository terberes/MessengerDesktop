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
    explicit Api(QJSEngine* qjsEnginePtr);
    Q_INVOKABLE void setUrl(const QString& url);
    Q_INVOKABLE QUrl getUrl();

    void handle_response(QNetworkReply* res);

//    Q_INVOKABLE Promise* getServerPrefs();
    Q_INVOKABLE Promise* sendCode(QString, CodeVerificationChannel);
    Q_INVOKABLE Promise* verifyCode(const QString& code, QString number);
    Q_INVOKABLE Promise* registerUser(const QString& token, const QString& firstName,
            const QString& lastName, const QString& username);

    QNetworkAccessManager* _manager;

private:
    static QString getApiChannelValue(CodeVerificationChannel);
    static QString& normalizeNumber(QString&);
    static const QString default_path_prefix; // = "/api"
    bool httpsEnabled = false;
    QUrl api_url(const QString& path);
    QUrl url;
    QList<Promise*> handles;
    QJSEngine* engine{};
signals:
};
