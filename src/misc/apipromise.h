#ifndef PROMISE_H
#define PROMISE_H

#include <QObject>

class Promise : public QObject
{
    Q_OBJECT
public:
    explicit Promise(QObject *parent = nullptr);

signals:

};

#endif // PROMISE_H
