#pragma once

#include <QObject>
#include <QVariant>
#include <QNetworkReply>

class ApiResult : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QVariant value READ get_value NOTIFY value_changed);
    Q_PROPERTY(QNetworkReply::NetworkError type READ get_type NOTIFY result_changed);
    
    explicit ApiResult(QObject *parent = nullptr);
    ApiResult(QNetworkReply::NetworkError result, QVariant value);
    ApiResult(QNetworkReply::NetworkError err);
    QVariant get_value();
    QNetworkReply::NetworkError get_type();
    QVariant _value;
    QNetworkReply::NetworkError _result;
signals:
    void value_changed(QVariant);
    void result_changed(QNetworkReply::NetworkError);
};

