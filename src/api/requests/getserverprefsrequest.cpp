#include "getserverprefsrequest.h"

ApiResult GetServerPrefsRequest::parse(QString raw)
{
    QJsonParseError err;
    auto jdoc = QJsonDocument::fromJson(raw.toUtf8(), &err);
    if (jdoc.isNull() || !jdoc.isObject())
        invalidResponse: return ApiResult {ApiResult::ApiResultType::INVALID_RESPONSE};
    auto json = jdoc.object();
    if (
            json.contains(QStringLiteral("realTimeServerIPv4")) && json["realTimeServerIpv4"].isString() &&
            json.contains(QStringLiteral("realTimeServerIPv6")) && json["realTimeServerIpv6"].isString() &&
            json.contains(QStringLiteral("realTimePortIPv4")) && json["realTimePortIPv4"].isDouble() &&
            json.contains(QStringLiteral("realTimePortIPv6")) && json["realTimePortIPv6"].isDouble()
            )
        return ApiResult {ApiResult::ApiResultType::SUCCESS, QVariant(json)};
    else goto invalidResponse;
}
