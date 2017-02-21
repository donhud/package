#include "dnetwork.h"
#include "QDebug"
#include "QApplication"
#include <QUrl>
#include <QtNetwork>

DNetwork::DNetwork(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(checkUpdates(QNetworkReply*)));
}
DNetwork::~DNetwork()
{
}

void DNetwork::checkForUpdates(bool silent)
{
    isSilentCheck = silent;
    QNetworkRequest request(QUrl("http://dfm.sourceforge.net/latest-version"));
    manager->get(request);
}

void DNetwork::checkUpdates(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << reply->errorString();
        return;}
    QString versionText;
    versionText = reply->readAll();
    double appVersion, LatestVersion;
    appVersion = QApplication::applicationVersion().toDouble();
    LatestVersion = versionText.toDouble();
    qDebug() << versionText << appVersion;

    if(appVersion == LatestVersion && isSilentCheck == false)
        emit latestVersionMsg();
    else if(appVersion > LatestVersion && isSilentCheck == false)
        emit developmentVersionMsg();
    else if(appVersion < LatestVersion) {
        emit needUpdate(LatestVersion);
    }

}

void DNetwork::showMsgLatest()
{
}

void DNetwork::showMsgDevel()
{
}
