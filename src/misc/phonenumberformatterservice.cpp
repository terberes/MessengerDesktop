#include "phonenumberformatterservice.h"
#include <phonenumbers/phonenumberutil.h>
#include <QDebug>
using i18n::phonenumbers::PhoneNumber;

PhoneNumberFormatterService::PhoneNumberFormatterService(QObject *parent) : QObject(parent)
{
    this->_locale = QLocale::system().name().split("_")[0].toStdString();
    this->_fmt = PhoneNumberUtil::GetInstance()->GetAsYouTypeFormatter(this->_locale);
    std::string temp_str;
    this->_fmt->InputDigit('+', &temp_str);
}
QString PhoneNumberFormatterService::number() {
    return this->_number;
}
Q_DECL_EXPORT bool PhoneNumberFormatterService::add_digit(QString str) {
    if (str != "+" && !str.back().isDigit()) return false;
    auto ch = str.toStdString().back();
    this->raw_num.push_back(ch);
    std::string res;
    this->_number = QString::fromLocal8Bit(this->_fmt->InputDigit(ch, &res).c_str());
    return true;
}
Q_DECL_EXPORT void PhoneNumberFormatterService::remove_digit() {
    if (this->_number == "+") return;
    this->_fmt->Clear();
    auto saved_num = this->raw_num;
    this->raw_num.clear();
    saved_num.pop_back();
    this->_number = "";
    std::string result;
    this->_fmt->InputDigit('+', &result);
    for (char& c : saved_num) {
        this->_fmt->InputDigit(c, &result);
        this->raw_num.push_back(c);
    }
    this->_number = QString::fromLocal8Bit(result.c_str());
}
Q_DECL_EXPORT bool PhoneNumberFormatterService::verify() {
    PhoneNumber num{};
    return !PhoneNumberUtil::GetInstance()->Parse(
                                this->_number.toStdString(),
                                this->_locale, &num)
            && PhoneNumberUtil::GetInstance()->IsValidNumber(num);
}
PhoneNumberFormatterService::~PhoneNumberFormatterService() {
    delete _fmt;
}
