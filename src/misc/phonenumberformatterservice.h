#pragma once

#include <phonenumbers/asyoutypeformatter.h>
#include <memory>
#include <QObject>
#include <QString>
using i18n::phonenumbers::AsYouTypeFormatter;
using i18n::phonenumbers::PhoneNumberUtil;

class PhoneNumberFormatterService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number)
public:
    explicit PhoneNumberFormatterService(QObject *parent = nullptr);
    QString number();
    ~PhoneNumberFormatterService();
    Q_INVOKABLE bool add_digit(QString str);
    Q_INVOKABLE void remove_digit();
    Q_INVOKABLE bool verify();
private:
    QString _number;
    AsYouTypeFormatter* _fmt;
    std::vector<char> raw_num;
    std::string _locale;
};

