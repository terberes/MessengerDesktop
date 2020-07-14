#ifndef SETTINGS_H
#define SETTINGS_H
#include<memory>
#include<QSettings>
#include<QCoreApplication>

class Settings
{
public:
    Settings();
    bool is_logged_in();
private:
    std::unique_ptr<QSettings> _app_settings;
};

#endif // SETTINGS_H
