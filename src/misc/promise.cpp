#include "promise.h"

Promise::Promise(QObject* parent) : QObject(parent) {}

Promise::Promise(
        Api* apiptr,
        QUrl url,
        std::function < QVariant(QNetworkReply*) > parsefn,
        QObject* parent) :
            QObject(parent), engine(qjsEngine(this)), api(apiptr), parse(parsefn) {
    this->req = QNetworkRequest{url};
    req.setOriginatingObject(this);
    api->_manager->get(req);
}
//QJSValue cbCopy(callback); // needed as callback is captured as const
//QJSEngine *engine = qjsEngine(this);
//cbCopy.call(QJSValueList { engine->toScriptValue(files) });
//watcher->deleteLater();

void Promise::handle_response(QNetworkReply* res) {
    auto err = res->error();
    if (err != QNetworkReply::NoError) {
        call_js_callback(_fail_callback, err);
    }

}

void Promise::call_js_callback(QJSValue callback, QVariant ret) {
    callback.call(QJSValueList { engine->toScriptValue(ret) });
}

Promise* Promise::then(QJSValue callback) {
    if (!callback.isCallable()) engine->throwError("'then' callback must be callable");
    this->_then_callback = std::move(callback); // Copying callback
    return this;
}
Promise* Promise::fail(QJSValue callback) {
    if (!callback.isCallable()) engine->throwError("'fail' callback must be callable");
    this->_fail_callback = std::move(callback);
    return this;
}
