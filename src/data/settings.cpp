#include "settings.h"
bool Settings::is_logged_in() {
    return this->_app_settings.contains("loggedIn") &&
            this->_app_settings.value("loggedIn").toBool();
}
