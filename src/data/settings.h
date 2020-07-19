#pragma once
#include <memory>
#include <QSettings>
#include <QCoreApplication>
#include <QUrl>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl realTimeServerIPv4)
public:
    explicit Settings(QObject* parent = nullptr);
    Q_INVOKABLE bool is_logged_in();
    Q_INVOKABLE void setRealTimeURLs(const QUrl& addrV4, const QUrl& addrV6, int portV4, int portV6);

private:
    QSettings _appSettings;
};

