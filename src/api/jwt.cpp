#include <QJsonDocument>
#include "jwt.h"

JWT JWT::authJWT(QByteArray encoded) {
    auto jwt = JWT(encoded);
    jwt.universalParse(encoded);
    jwt.authParse();
    return std::move(jwt);
}

JWT JWT::accessJWT(QByteArray encoded) {
    auto jwt = JWT(encoded);
    jwt.universalParse(encoded);
    jwt.accessParse();
    return std::move(jwt);
}

bool JWT::isExpired() {
    return expiresAt < QDateTime::currentDateTime();
}

void JWT::universalParse(QByteArray arr) {
    auto parts = arr.split('.');
    if (parts.count() == 3) throw std::runtime_error("JWT must have 3 dot-separated parts");
    auto headerDoc = QJsonDocument::fromJson(QByteArray::fromBase64(parts[0]));
    if (!(headerDoc.isObject()
          && headerDoc.object()["typ"].toString("") == "JWT"
          && headerDoc.object()["alg"].toString("") == "HS256"))
        throw std::runtime_error("JWT must have valid header");
    header = headerDoc.object();
    auto bodyDoc = QJsonDocument::fromJson(QByteArray::fromBase64(parts[1]));
    if (!(bodyDoc.isObject()
          && body["iss"].isString()
          && body["aud"].isString()
          && body["exp"].isDouble()
          && body["type"].isString()))
        throw std::runtime_error("JWT must have valid json object body");
    body = bodyDoc.object();
    expiresAt = QDateTime::fromSecsSinceEpoch(body["exp"].toDouble());
}

void JWT::authParse() {
    if (!(body["num"].isString()
          && body["type"].toString("") == "auth"))
        throw std::runtime_error("Invalid Auth JWT");
    type = Type::Auth;
}

void JWT::accessParse() {
    if (!(body["jti"].isString()
            && body["uid"].isString()
            && body["type"].toString("") == "access"))
        throw std::runtime_error("Invalid Access JWT");
}