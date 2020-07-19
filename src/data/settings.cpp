#include "settings.h"
Settings::Settings(QObject* parent) : QObject(parent), _appSettings("yakuri354", "MessengerDesktop") {}
bool Settings::is_logged_in() {
    return this->_appSettings.contains("loggedIn") &&
           this->_appSettings.value("loggedIn").toBool();
}

void Settings::setRealTimeURLs(const QUrl& addrV4, const QUrl& addrV6, int portV4, int portV6) {
    _appSettings.setValue("realTimeAddressIPv4", addrV4);
    _appSettings.setValue("realTimeAddressIPv6", addrV6);
    _appSettings.setValue("realTimePortIPv4", portV4);
    _appSettings.setValue("realTimePortIPv6", portV6);
}
