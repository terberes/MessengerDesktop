#pragma once
#include "../apirequest.h"

class GetServerPrefsRequest : ApiRequest
{
public:
    ApiResult parse(QString raw) override;
    QString path = "/getConnPrefs";
    bool isAuthorized = false;
};

