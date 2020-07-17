#pragma once
#include <QObject>
#include "apiresult.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class ApiRequest : public QObject {
    Q_OBJECT
public:
    explicit ApiRequest(QObject* parent = nullptr);
    QString path;
    bool is_authorized;
    virtual ApiResult parse(QString raw) = 0;
protected:
    static const QString base_path; // "/api"
};
