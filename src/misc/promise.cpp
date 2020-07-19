#include "promise.h"

#include <utility>

Promise::Promise(QObject* parent) : QObject(parent) { }

Promise::Promise(
        std::function<QVariant(QNetworkReply*)> parseFunc,
        [[maybe_unused]] QJSEngine* jsEngine,
        QObject* parent) :
        QObject(parent), engine(jsEngine != nullptr ? jsEngine : qjsEngine(this)),
        parse(std::move(parseFunc)) { }

void Promise::handle_response(QNetworkReply* res) {
    auto err = res->error();
    if (err != QNetworkReply::NoError) {
        qDebug() << "Error " << res->errorString() << " occurred";
        qDebug() << res->readAll();
        call_js_callback(_fail_callback,
                         QJSValueList{ engine->toScriptValue(err), engine->toScriptValue(res->errorString()) });
        return;
    }
    auto retval = parse(res);
    if (retval.canConvert<int>() && retval.toInt() != 0) call_js_callback(_fail_callback, retval);
    else call_js_callback(_then_callback, retval);
}

void Promise::call_js_callback(QJSValue callback, const QJSValueList &vals) {
    callback.call(vals);
}

void Promise::call_js_callback(QJSValue callback, const QVariant &ret) {
    call_js_callback(std::move(callback), QJSValueList{ engine->toScriptValue(ret) });
}

Promise* Promise::then(QJSValue callback) {
    if (!callback.isCallable()) {
        engine->throwError("'then' callback must be callable");
        return this;
    }
    this->_then_callback = std::move(callback); // Copying callback
    return this;
}

Promise* Promise::fail(QJSValue callback) {
    if (!callback.isCallable()) {
        engine->throwError("'fail' callback must be callable");
        return this;
    }
    this->_fail_callback = std::move(callback);
    return this;
}
