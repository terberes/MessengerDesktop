#include "settings.h"

Settings::Settings()
{
    QCoreApplication::setOrganizationName("yakuri354");
    QCoreApplication::setOrganizationDomain("example.com");
    QCoreApplication::setApplicationName("MessengerDesktop");
    this->_app_settings = std::make_unique<QSettings>();
}
bool Settings::is_logged_in() {
    return this->_app_settings->contains("loggedIn") &&
            this->_app_settings->value("loggedIn").toBool();
}
