#pragma once
#include <memory>
#include <QSettings>
#include <QCoreApplication>
#include <QUrl>
#include <QDateTime>
#include "../api/jwt.h"

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ getUrl WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QDateTime sentCodeAt READ getSentCodeAt NOTIFY codeSent)
public:
    explicit Settings(QObject* parent = nullptr);
    Q_INVOKABLE bool is_logged_in();
    void setUrl(const QUrl& address);
    QUrl getUrl();
    Q_INVOKABLE bool isUrlSet();

    QDateTime getSentCodeAt();
    Q_INVOKABLE void sendCode();
    Q_INVOKABLE bool codeExpired();

    JWT getRegisterToken();
    void setRegisterToken(JWT token);
    bool registerExpired();
private:
    QSettings _appSettings;
signals:
    void urlChanged();
    void codeSent();
};

