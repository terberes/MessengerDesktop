#pragma once

#include <QObject>
#include <QJSValue>
#include <QNetworkReply>
#include <QJSEngine>
class Promise : public QObject
{
    Q_OBJECT
public:
    explicit Promise(QObject *parent = nullptr);
    explicit Promise(std::function<QVariant (QNetworkReply*)> parseFunc,
                     [[maybe_unused]] QJSEngine* engine = nullptr,
            QObject* parent = nullptr);

    Q_INVOKABLE Promise* then(QJSValue callback);
    Q_INVOKABLE Promise* fail(QJSValue callback);

    void handle_response(QNetworkReply* res);
private:
    static void call_js_callback(QJSValue callback, const QJSValueList& vals);
    void call_js_callback(QJSValue callback, const QVariant& ret);
    QJSValue _then_callback;
    QJSValue _fail_callback;
    QJSEngine* engine{};
    std::function<QVariant (QNetworkReply*)> parse;
signals:

};
