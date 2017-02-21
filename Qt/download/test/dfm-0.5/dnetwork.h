#ifndef DNETWORK_H
#define DNETWORK_H

#include <QObject>
#include <QtNetwork>

class DNetwork : public QObject
{
    Q_OBJECT

public:
    explicit DNetwork(QObject *parent = 0);
    void checkForUpdates(bool silent = false);
    ~DNetwork();
    
signals:
    
public slots:

private slots:
    void checkUpdates(QNetworkReply *reply);

private:
    void showMsgLatest();
    void showMsgDevel();
    QNetworkAccessManager *manager;
    bool isSilentCheck;

signals:
    void latestVersionMsg();
    void developmentVersionMsg();
    void needUpdate(double version);
    
};

#endif // DNETWORK_H
