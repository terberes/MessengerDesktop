#ifndef API_H
#define API_H

#include <QObject>
#include <cpprest/http_client.h>

class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(QObject *parent = nullptr);

signals:

};

#endif // API_H
