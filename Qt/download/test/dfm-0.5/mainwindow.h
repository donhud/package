#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "contextmenu.h"
#include "infodlg.h"
#include "tabbar.h"
#include "icondlg.h"
#include "progressdlg.h"
#include "texteditor.h"
#include "customactionsdlg.h"
#include "dlistview.h"
#include "desktopapp.h"
#include "configdialog.h"
#include "Hmainwindow.h"
#include "dfilesystemmodel.h"
#include "dnetwork.h"
#include "dfileengine.h"
/** \mainpage
Dino is a simple file manger for GNU/Linux written on Qt.

\version Version 0.4
*/
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //! Change current path
    /*!
      Change current path in the file browser
      \param sPath Path to change
      \param remember Remember path to the history
      */
    void SetPath(QString sPath,bool remember = true);
    QString formatSize(qint64 num);
    QString currentPath;
    //! Convert string to boolean
    bool StringToBool(QString);
public slots:
    //! Run dino text editor
    void RunEditor(QString path);
    //! Run Hex Editor
    //! \param path Path to file
    void RunHexEditor(QString path = "");

private slots:    
    void ViewActivated();
    //! Change path to the parent
    void GoUp();
    //! Change path to home dir
    void GoHome();

    void slotgo();

    void RunEditor2();
    //! Run About Dialog
    void AboutDlg();
    //! Change path to the root dir
    void GoRoot();

    void ZoomIn();

    void ZoomOut();
    //! Change path tot the desktop dir
    void GoDesktop();

    void GoDocs();

    void GoPictures();

    void GoMusic();

    void GoMovies();

    void GoApps();

    void FeedBack();
    //! Make new file
    bool MakeFile();
    //! Make new dir
    bool MakeDir();

    void ContextMenu(QPoint pos);

    void RenameFile();

    void deleteFile();

    void slothidefiles();

    void scrollToTop();

    void scrollToBottom();

    void tabChanged(int index);

    void tabClose(int index);

    void addNewTab();

    void refreshview();

    void openFile();

    void runFile();
    //! Run properties dialog
    void InfoBoxRun();

    void goDrives();
    //! Run terminal
    void terminalRun();

    void tabsTop_toogled();

    void layoutLock_toogled();

    void scrollcurrent();

    void simplev_toogled();

    void thumbUpdate(QModelIndex);

    void clipboardChanged();

    void pasteLauncher(const QMimeData * data, QString newPath, QStringList cutList);

    void cutFile();

    void clearCutItems();

    void copyFile();

    bool cutCopyFile(QString source, QString dest, qint64 totalSize, bool cut);

    bool pasteFile(QList<QUrl> files,QString newPath, QStringList cutList);

    bool copyFolder(QString, QString, qint64, bool);

    void pasteClipboard();

    void progressFinished(int ret,QStringList newFiles);

    void EditFile();

    void goBack();

    void goForward();

    void tv_toogled();

    void editCustomActions();

    void mkSymLink();

    void actionMapper(QString);

    void customActionError(QProcess::ProcessError error);

    void customActionFinished(int ret);

    void readCustomActions();

    void treeMode_toogled();

    void RunSettingsDlg();

    void EditHexFile();

    void loadthumbs();

    void dirLoaded(QString);

    void selectByPtr();

    void loadTheme(QString themeFile);

    void clearSelection();

    void selectAll();

    void checkForUpdates();

    void showMsgDinoLatest();

    void showMsgDinoDevel();

    void needDinoUpdate(double version);

    void TemplateFileMapper(QString name);

    void clearClipboard();



signals:
    void updateCopyProgress(qint64, qint64, QString);
    void copyProgressFinished(int,QStringList);


protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    ProgressDialog * progress;
    DFileSystemModel *model;
    QSortFilterProxyModel *modell;
    QLineEdit *location;
    tabbar *tabs;
    DListView *FileView;
    int icosize;
    int ToolBarIconSize;
    QStack<QString> history;
    QStack<QString> future;
    QString term;
    QToolButton *go_bt;
    QToolButton *back_bt;
    QToolButton *forward_bt;
    QToolButton *home_bt;
    QToolBar *locationbar;
    QToolButton *up_bt;
    QToolButton *hide_bt;
    QCompleter *completer;
    QLabel * statusSize;
    QLabel * statusName;
    QLabel * statusDate;
    QFileInfo curIndex;
    QDirModel *completerModel;
    QToolButton *cut_bt;
    QToolButton *copy_bt;
    QToolButton *paste_bt;
    QToolButton *del_bt;
    QSignalMapper  *runCommandMappper;
    QList<QAction*> *actionList;
    QMultiHash<QString,QAction*> *customActions;
    QMultiHash<QString,QMenu*> *customMenus;
    QSignalMapper *FileTemplateMapper;
    QList<QAction*> FileTemplatesAction;
    bool pasteEnabled;
    bool eventFilter(QObject *obj, QEvent *ev);
    void hiddenset(bool temp);
    void error(QString text);
    void LocationRefresh();
    void writeSettings();
    void readSettings();
    void setPaste(bool);
    void recurseFolder(QString path, QString parent, QStringList *);
    void connectSignals();
    void onClose();
    QStringList getFileTemplates();
    void readFileTemplates();
};
//---------------------------------------------------------------------------------
class viewSortProxyModel : public QSortFilterProxyModel
{
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};
QString formatSize(qint64);

#endif // MAINWINDOW_H
