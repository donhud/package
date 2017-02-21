#include "dfileengine.h"

DFileEngine::DFileEngine()
{
}
bool DFileEngine::rmFolder(const QString sourceFolder)
{
    QDir dir(sourceFolder);
    if (!dir.exists())
        return true;
    foreach(const QFileInfo &info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden)) {
        if (info.isDir()) {
            if (!rmFolder(info.filePath()))
                return false;
        } else {
            if (!dir.remove(info.fileName()))
                return false;
        }
    }
    QDir parentDir(QFileInfo(sourceFolder).path());
    return parentDir.rmdir(QFileInfo(sourceFolder).fileName());
}
bool DFileEngine::remove(const QString path)
{
    if(!QFileInfo(path).exists())
        return false;
    else if (QFileInfo(path).isDir())
        return rmFolder(path);
    else if (!QFileInfo(path).isDir())
        return QFile::remove(path);
}
