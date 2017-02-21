#ifndef DESKTOPAPP_H
#define DESKTOPAPP_H
#include <QtCore>

class DesktopApp : public QObject
{
    Q_OBJECT
public:
    explicit DesktopApp(QObject *parent = 0);
    bool init(const QString& path);
    void launch();

    const bool isNoDisplay() const { return m_isNoDisplay; }
    //! Return true if type is url
    const bool isURL() const { return m_isURL; }
    //! Return path of desktop file
    const QString& path() const { return m_path; }
    const QString& url() const { return m_url; }
    //! Return Name of app of desktop file
    const QString& name() const { return m_name; }
    //! Return icon name of desktop file
    const QString& iconName() const { return m_iconName; }
    //! Return icon from desktop file
    QIcon getIcon();
    bool isNoIcon();
    const QStringList& categories() const { return m_categories; }

private:
    QString m_path;
    QDateTime m_lastUpdated;

    bool m_isNoDisplay;
    bool m_isURL;
    QString m_name;
    QString m_exec;
    QString m_iconName;
    QString m_url;
    QStringList m_categories;

};

#endif // DESKTOPAPP_H
