/****************************************************************************
*   Dino - simple file manager
*   Copyright (C) 2012  Dino project

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#include "desktopapp.h"
#include <QDesktopServices>
#include <QIcon>
#include <QStyle>
#include <QtCore>

DesktopApp::DesktopApp(QObject *parent)
    : QObject(parent)
{
}
bool DesktopApp::init(const QString& path)
{
    m_path = path;

    QFile file(m_path);

    if(!file.exists())
        return false;
    QFileInfo fileInfo(path);
    m_lastUpdated = fileInfo.lastModified();
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(line[0] == '[')
        {
            if(line.contains("Desktop Entry"))
                continue;
            else
                break; // We only process "Desktop Entry" here.
        }
        if(line[0] == '#')
            continue;
        QStringList list = line.split('=');
        if(list.size() < 2)
            continue;
        QString key = list[0];
        QString value = list[1];
        if(key == "NoDisplay" && value == "true")
            m_isNoDisplay = true;
        if(key == "Type" && value == "Link")
            m_isURL = true;
        if(key == "Name["+(QLocale::system().name())+"]")
            m_name = value;
        if(key == "Name")
            m_name = value;
        if(key == "URL")
            m_url = value;
        if(key == "Exec")
            m_exec = value;
        if(key == "Icon")
        {
            m_iconName = value;
        }
        if(key == "Categories")
            m_categories = value.split(";", QString::SkipEmptyParts);
    }

    return true;
}

void DesktopApp::launch()
{
    QString exec = m_exec;
    if(m_isURL && !m_url.isEmpty()) {
        QDesktopServices::openUrl(m_url);
        return;
    }
    if(exec.isEmpty()) return;

    // Handle special arguments.
    for(;;) {
        int argPos = exec.indexOf('%');
        if(argPos == -1)
            break;
        // For now, just remove them.
        int spacePos = exec.indexOf(' ', argPos);
        if(spacePos == -1)
            exec.resize(argPos);
        else
            exec.remove(argPos, spacePos - argPos);
    }

    exec = exec.trimmed();
    QStringList args = exec.split(' ');
    QString process = args[0];
    args.removeAt(0);
    QProcess::startDetached(process, args);
}

bool DesktopApp::isNoIcon()
{
    return m_iconName.isEmpty();
}

QIcon DesktopApp::getIcon()
{
    if(!m_iconName.isEmpty()) {
        if(QFile::exists(m_iconName))
            return QIcon(m_iconName);
        else if(QIcon::hasThemeIcon(m_iconName))
            return QIcon::fromTheme(m_iconName);
        else if(QFile::exists("/usr/share/pixmaps/"+(m_iconName)+".png"))
            return QIcon("/usr/share/pixmaps/"+(m_iconName)+".png");
        else if(QFile::exists("/usr/share/pixmaps/"+(m_iconName)))
            return QIcon("/usr/share/pixmaps/"+(m_iconName));
        else if(QFile::exists("/usr/share/pixmaps/"+(m_iconName)+".xpm"))
            return QIcon("/usr/share/pixmaps/"+(m_iconName)+".xpm");
        else if(QFile::exists("/usr/share/icons/"+(m_iconName)+".png"))
            return QIcon("/usr/share/icons/"+(m_iconName)+".png");
        else
            return QIcon::fromTheme("application-x-desktop");
    }

}
