#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent), _appSettings("yakuri354", "MessengerDesktop") {}

bool Settings::is_logged_in() {
    return this->_appSettings.contains("loggedIn") &&
           this->_appSettings.value("loggedIn").toBool();
}

void Settings::setUrl(const QUrl &address) {
    _appSettings.setValue("url", address);
    emit urlChanged();
}

QUrl Settings::getUrl() {
    if (_appSettings.contains("url"))
        return _appSettings.value("url").toUrl();
    return QUrl();
}

bool Settings::isUrlSet() {
    return _appSettings.contains("url") && !_appSettings.value("url").toUrl().isEmpty();
}

void Settings::sendCode() {
    _appSettings.setValue("sentCodeAt", QDateTime::currentDateTimeUtc());
    emit codeSent();
}

QDateTime Settings::getSentCodeAt() {
    return _appSettings.value("sentCodeAt").toDateTime();
}

bool Settings::codeExpired() {
    return !(_appSettings.contains("sentCodeAt")
             && _appSettings.value("sentCodeAt").isValid()
             && _appSettings.value("sentCodeAt").toDateTime() > QDateTime::currentDateTimeUtc());
}
