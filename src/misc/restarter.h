#pragma once
#include <QObject>


class Restarter : public QObject
{
Q_OBJECT

public:
    explicit Restarter(QObject *parent = nullptr);
    Q_INVOKABLE void restart();

signals:

public slots:
};
