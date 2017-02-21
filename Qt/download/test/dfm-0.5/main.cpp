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
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Dino");
    a.setApplicationVersion("0.5");
    a.setOrganizationName("Dino");
    a.setOrganizationDomain("dino.org");

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(("Dino_") + locale),qApp->applicationDirPath()+(QDir::separator())+"translations");
    a.installTranslator(&translator);

    MainWindow w;

    QDir dir(QDir::homePath());
    if (a.arguments().count()>1){
        if (dir.exists(a.arguments().at(1)))
        {
            dir.setPath(a.arguments().at(1));
        }
        else if(a.arguments().at(1) == "--texteditor")
        {
            w.RunEditor("");
            return a.exec();
        }
        else if(a.arguments().at(1).startsWith("--texteditor="))
        {
            QString str(a.arguments().at(1));
            str.remove("--texteditor=");
            w.RunEditor(str);
            return a.exec();
        }
        else if(a.arguments().at(1) == "--hexeditor")
        {
            w.RunHexEditor("");
            return a.exec();
        }
        else if(a.arguments().at(1) == "--desktop")
        {
            dir.setPath(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));
        }
        else if(a.arguments().at(1) == "--documents")
        {
            dir.setPath(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation));
        }
        else if(a.arguments().at(1) == "--pictures")
        {
            dir.setPath(QDesktopServices::storageLocation(QDesktopServices::PicturesLocation));
        }
        else if(a.arguments().at(1) == "--music")
        {
            dir.setPath(QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
        }
        else if(a.arguments().at(1) == "--movies")
        {
            dir.setPath(QDesktopServices::storageLocation(QDesktopServices::MoviesLocation));
        }
        else if(a.arguments().at(1) == "--root")
        {
            dir.setPath(QDir::rootPath());
        }
    }
    w.currentPath = dir.path();
    w.SetPath(dir.path());
    w.show();

    return a.exec();
}
