#pragma once
#include <memory>
#include <QSettings>
#include <QCoreApplication>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl realTimeServerIPv4)
public:
    explicit Settings(QObject* parent = nullptr) : QObject(parent), _app_settings("yakuri354", "MessengerDesktop") {}
    Q_INVOKABLE bool is_logged_in();

private:
    QSettings _app_settings;
};

