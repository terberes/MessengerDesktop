//
// Created by yakuri354 on 7/20/20.
//

#include "restarter.h"

#include "restarter.h"
#include <QGuiApplication>
#include <QProcess>


Restarter::Restarter(QObject *parent) :
        QObject (parent)
{
}

void Restarter::restart()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments()); //application restart
}
