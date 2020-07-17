#pragma once

#include <QObject>
#include <QJSValue>
#include <QNetworkReply>
#include <QJSEngine>

class Api;
class Promise : public QObject
{
    Q_OBJECT
public:
    explicit Promise(QObject *parent = nullptr);
    Promise(Api* api, QUrl url, std::function<QVariant (QNetworkReply*)> parse, QObject* parent = nullptr);

    Q_INVOKABLE Promise* then(QJSValue callback);
    Q_INVOKABLE Promise* fail(QJSValue callback);

    void handle_response(QNetworkReply* res);
    ~Promise();
private:
    void call_js_callback(QJSValue callback, QVariant ret);
    QNetworkRequest req;
    QJSValue _then_callback;
    QJSValue _fail_callback;
    QJSEngine* engine;
    Api* api;
    std::function<QVariant (QNetworkReply*)> parse;
signals:

};
#include "../api/api.h"
