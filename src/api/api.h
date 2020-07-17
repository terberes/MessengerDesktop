#pragma once

#include <QObject>
#include <exception>
#include <QNetworkAccessManager>
#include "../misc/promise.h"
#include "requests/getserverprefsrequest.h"
#include <QNetworkReply>

class Api : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString base_url READ get_base_url WRITE set_base_url NOTIFY base_url_changed)
public:
    explicit Api(QObject *parent = nullptr);
    void set_base_url(QString url);
    QString get_base_url();

    void handle_response(QNetworkReply* res);

    Q_INVOKABLE Promise* get_server_preferences();
    QNetworkAccessManager* _manager;

private:
    static const QString path_prefix; // = "/api"
    QString base_url;
    QUrl api_url(QString path);
    QList<Promise*> handles;
signals:
    void base_url_changed();
};
