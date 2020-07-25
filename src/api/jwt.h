#pragma once
#include <QObject>
#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <utility>

struct JWT { // This is NOT intended for general use, API only
//    explicit JWT(QByteArray base64Enc, bool& err);
//    explicit JWT(QString base64EncString);
    static JWT authJWT(QByteArray encoded);
    static JWT accessJWT(QByteArray encoded);

    enum class Type {
        Auth,
        Access,
        Unknown
    };

    bool isExpired();

private:
    Q_GADGET
    explicit JWT(QByteArray rawArr) : raw(std::move(rawArr)) {}
    QByteArray raw;
    QJsonObject header;
    QJsonObject body;
    QDateTime expiresAt;
    Type type;

    void universalParse(QByteArray arr);
    void authParse();
    void accessParse();
};
