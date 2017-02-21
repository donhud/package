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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#ifdef Q_OS_UNIX
#include <sys/vfs.h>
#endif
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    model = new DFileSystemModel(this);
    model->setReadOnly(false);
    model->setResolveSymlinks(true);
    modell = new viewSortProxyModel();
    modell->setSourceModel(model);
    modell->setSortCaseSensitivity(Qt::CaseInsensitive);


    FileView = new DListView(this);
    ui->verticalLayout_2->addWidget(FileView);
    tabs = new tabbar;
    ui->verticalLayout->addWidget(tabs);
    ui->gridLayout->setContentsMargins(0,0,0,0);
    ui->verticalLayout->setContentsMargins(0,0,0,0);
    tabs->setDrawBase(0);
    tabs->setExpanding(0);
    ui->gridLayout->setSpacing(0);
    FileView->setModel(modell);
    FileView->setEnabled(true);
    FileView->installEventFilter(this);
    runCommandMappper = new QSignalMapper();
    customActions = new QMultiHash<QString,QAction*>;
    FileTemplateMapper = new QSignalMapper();

    cut_bt = new QToolButton;
    cut_bt->setIcon(QIcon::fromTheme("edit-cut",QIcon(":/files/faenza/edit-cut.png")));
    cut_bt->setStatusTip(tr("Move selected files"));
    QObject::connect(cut_bt,SIGNAL(clicked()),SLOT(cutFile()));
    copy_bt = new QToolButton;
    copy_bt->setIcon(QIcon::fromTheme("edit-copy",QIcon(":/files/faenza/edit-copy.png")));
    copy_bt->setStatusTip(tr("Copy selected files to clipboard"));
    QObject::connect(copy_bt,SIGNAL(clicked()),SLOT(copyFile()));
    paste_bt = new QToolButton;
    paste_bt->setIcon(QIcon::fromTheme("edit-paste",QIcon(":/files/faenza/edit-paste.png")));
    paste_bt->setStatusTip(tr("Paste files from clipboard"));
    QObject::connect(paste_bt,SIGNAL(clicked()),SLOT(pasteClipboard()));
    del_bt = new QToolButton;
    del_bt->setIcon(QIcon::fromTheme("edit-delete",QIcon(":/files/faenza/edit-delete.png")));
    del_bt->setStatusTip(tr("Delete selected files"));
    QObject::connect(del_bt,SIGNAL(clicked()),SLOT(deleteFile()));
    ui->opToolbar->addWidget(cut_bt);
    ui->opToolbar->addWidget(copy_bt);
    ui->opToolbar->addWidget(paste_bt);
    ui->opToolbar->addWidget(del_bt);

    location = new QLineEdit(this);
    location->setAcceptDrops(true);
    location->setDragEnabled(true);
    location->installEventFilter(this);

    go_bt = new QToolButton;
    go_bt->setIcon(QIcon::fromTheme("go-jump",QIcon(":/files/faenza/go-jump.png")));
    home_bt = new QToolButton;
    home_bt->setIcon(QIcon::fromTheme("go-home",QIcon(":/files/faenza/go-home.png")));
    up_bt = new QToolButton;
    up_bt->setIcon(QIcon::fromTheme("go-up",QIcon(":/files/faenza/go-up.png")));
    hide_bt = new QToolButton;
    hide_bt->setIcon(QIcon::fromTheme("system-run",QIcon(":/files/faenza/system-run.png")));
    hide_bt->setText(tr("Show hidden files"));
    hide_bt->setStatusTip(tr("Show hidden files"));
    hide_bt->setCheckable(true);
    back_bt = new QToolButton;
    back_bt->setIcon(QIcon::fromTheme("go-previous",QIcon(":/files/faenza/go-previous.png")));
    forward_bt = new QToolButton;
    forward_bt->setIcon(QIcon::fromTheme("go-next",QIcon(":/files/faenza/go-next.png")));
    QObject::connect(go_bt,SIGNAL(clicked()),this,SLOT(slotgo()));
    QObject::connect(home_bt,SIGNAL(clicked()),this,SLOT(GoHome()));
    QObject::connect(up_bt,SIGNAL(clicked()),this ,SLOT(GoUp()));
    QObject::connect(hide_bt,SIGNAL(toggled(bool)),this,SLOT(slothidefiles()));

    ui->locationbar->addWidget(back_bt);
    ui->locationbar->addWidget(up_bt);
    ui->locationbar->addWidget(home_bt);
    ui->locationbar->addWidget(forward_bt);
    ui->locationbar->addWidget(location);
    ui->locationbar->addWidget(go_bt);

    ui->mainToolBar->addAction(QIcon::fromTheme("zoom-in",QIcon(":/files/faenza/zoom-in.png")),"zoom in",this,SLOT(ZoomIn()))->setStatusTip(tr("Zoom in icons in the view"));
    ui->mainToolBar->addAction(QIcon::fromTheme("zoom-out",QIcon(":/files/faenza/zoom-out.png")),"zoom out",this,SLOT(ZoomOut()))->setStatusTip(tr("Zoom out icons in the view"));
    ui->mainToolBar->addWidget(hide_bt);
    ui->mainToolBar->setIconSize(QSize(25,25));

    completerModel = new QDirModel;
    completerModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    completer = new QCompleter;
    completer->setModel(completerModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    location->setCompleter(completer);

    ui->actionMake_SymLink->setStatusTip(tr("Make Symlink for selected file"));
    ui->menuHelp->addAction(QIcon::fromTheme("mail-send"),tr("Feedback"),this,SLOT(FeedBack()));
    ui->menuHelp->addAction(QIcon::fromTheme("help-about"),tr("About"),this,SLOT(AboutDlg()));
    ui->menuGo_to->addAction(QIcon::fromTheme("user-home"),tr("Home"),this,SLOT(GoHome()));
#ifdef Q_OS_MAC
    ui->menuGo_to->addAction(QIcon::fromTheme("application-x-executable"),"Apps",this,SLOT(GoApps()));
#endif
    ui->menuGo_to->addAction(QIcon::fromTheme("user-desktop"),tr("Desktop"),this,SLOT(GoDesktop()));
    ui->menuGo_to->addAction(QIcon::fromTheme("text-x-generic"),tr("Documents"),this,SLOT(GoDocs()));
    ui->menuGo_to->addAction(QIcon::fromTheme("image-x-generic"),tr("Pictures"),this,SLOT(GoPictures()));
    ui->menuGo_to->addAction(QIcon::fromTheme("audio-x-generic"),tr("Music"),this,SLOT(GoMusic()));
    ui->menuGo_to->addAction(QIcon::fromTheme("video-x-generic"),tr("Movies"),this,SLOT(GoMovies()));
    ui->menuGo_to->addSeparator();
    ui->menuGo_to->addAction(QIcon::fromTheme("drive-harddisk",QIcon(":/files/faenza/drive-harddisk.png")),tr("Drives"),this,SLOT(goDrives()));
    ui->menuGo_to->addAction(QIcon::fromTheme("computer",QIcon(":/files/faenza/computer.png")),tr("Root"),this,SLOT(GoRoot()));
    ui->statusBar->setSizeGripEnabled(true);
    actionList = new QList<QAction*>;

    //EditActions
    QObject::connect(ui->actionCut,SIGNAL(triggered()),SLOT(cutFile()));
    ui->actionCut->setShortcut(QKeySequence::Cut);
    QObject::connect(ui->actionCopy,SIGNAL(triggered()),SLOT(copyFile()));
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    QObject::connect(ui->actionPaste,SIGNAL(triggered()),SLOT(pasteClipboard()));
    ui->actionPaste->setShortcut(QKeySequence::Paste);

    //Set icons
    ui->actionExit->setIcon(QIcon::fromTheme("application-exit"));
    ui->actionNew_folder->setIcon(QIcon::fromTheme("folder-new"));
    ui->actionRun_terminal->setIcon(QIcon::fromTheme("utilities-terminal"));
    ui->actionAdd_new_tab->setIcon(QIcon::fromTheme("list-add"));
    ui->actionRemove->setIcon(QIcon::fromTheme("edit-delete"));
    ui->actionCopy->setIcon(QIcon::fromTheme("edit-copy"));
    ui->actionCut->setIcon(QIcon::fromTheme("edit-cut"));
    ui->actionPaste->setIcon(QIcon::fromTheme("edit-paste"));
    ui->actionEdit_File->setIcon(QIcon::fromTheme("accessories-text-editor"));
    ui->actionText_Editor->setIcon(QIcon::fromTheme("accessories-text-editor"));
    ui->actionSettings->setIcon(QIcon::fromTheme("preferences-desktop"));
    ui->actionZoom_in->setIcon(QIcon::fromTheme("zoom-in"));
    ui->actionZoom_out->setIcon(QIcon::fromTheme("zoom-out"));
    ui->actionRefresh->setIcon(QIcon::fromTheme("view-refresh"));

    ui->actionZoom_in->setShortcut(QKeySequence::ZoomIn);
    ui->actionZoom_out->setShortcut(QKeySequence::ZoomOut);
    ui->actionAdd_new_tab->setShortcut(QKeySequence::AddTab);
    ui->actionSelect_All->setShortcut(QKeySequence::SelectAll);
    ui->actionRemove->setShortcut(QKeySequence::Delete);

    ui->actionCheck_for_updates->setVisible(false);

    FileView->setContextMenuPolicy(Qt::CustomContextMenu);

    connectSignals();
    readSettings();
    readCustomActions();
    setPaste(false);

    if(!QFile::exists(QDir::homePath()+QDir::separator()+"Templates")) {
        QDir dirTmp(QDir::homePath());
        dirTmp.mkdir("Templates");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete modell;
    delete location;
    delete tabs;
    delete FileView;
    delete completerModel;
    delete actionList;
    delete completer;
    delete runCommandMappper;
    delete FileTemplateMapper;
    delete paste_bt;
    delete cut_bt;
    delete home_bt;
    delete up_bt;
    delete hide_bt;
    delete go_bt;
    delete back_bt;
    delete del_bt;
    delete copy_bt;
    delete customMenus;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    onClose();
    event->accept();
}

void MainWindow::onClose()
{
    model->cacheInfo();
    QApplication::clipboard()->clear();
    writeSettings();
}
void MainWindow::connectSignals()
{
    QObject::connect(ui->actionHex_Editor, SIGNAL(activated()), this, SLOT(RunHexEditor()));
    QObject::connect(ui->actionSettings, SIGNAL(activated()),this,SLOT(RunSettingsDlg()));
    QObject::connect(ui->actionTree_Mode, SIGNAL(toggled(bool)),this, SLOT(treeMode_toogled()));
    QObject::connect(runCommandMappper, SIGNAL(mapped(QString)),this, SLOT(actionMapper(QString)));
    QObject::connect(FileTemplateMapper, SIGNAL(mapped(QString)),this, SLOT(TemplateFileMapper(QString)));
    QObject::connect(FileView,SIGNAL(activated(QModelIndex)),this,SLOT(ViewActivated()));
    QObject::connect(ui->actionNew_folder,SIGNAL(activated()),SLOT(MakeDir()));
    QObject::connect(ui->actionRemove,SIGNAL(activated()),SLOT(deleteFile()));
    QObject::connect(FileView,SIGNAL(customContextMenuRequested(QPoint)),SLOT(ContextMenu(QPoint )));
    QObject::connect(ui->actionGo_to_url,SIGNAL(activated()),SLOT(slotgo()));
    QObject::connect(ui->actionZoom_in,SIGNAL(activated()),SLOT(ZoomIn()));
    QObject::connect(ui->actionRun_terminal,SIGNAL(activated()),SLOT(terminalRun()));
    QObject::connect(ui->actionZoom_out,SIGNAL(activated()),SLOT(ZoomOut()));
    QObject::connect(ui->actionScroll_to_top,SIGNAL(activated()),SLOT(scrollToTop()));
    QObject::connect(ui->actionScroll_to_bottom,SIGNAL(activated()),SLOT(scrollToBottom()));
    QObject::connect(tabs,SIGNAL(tabCloseRequested(int)),SLOT(tabClose(int)));
    QObject::connect(tabs,SIGNAL(currentChanged(int)),SLOT(tabChanged(int)));
    QObject::connect(ui->actionAdd_new_tab,SIGNAL(activated()),SLOT(addNewTab()));
    QObject::connect(ui->actionRefresh,SIGNAL(activated()),SLOT(refreshview()));
    QObject::connect(ui->actionTabs_on_top,SIGNAL(toggled(bool)),SLOT(tabsTop_toogled()));
    QObject::connect(ui->actionLock_layout,SIGNAL(toggled(bool)),SLOT(layoutLock_toogled()));
    QObject::connect(ui->actionScroll_to_selected_item,SIGNAL(activated()),SLOT(scrollcurrent()));
    QObject::connect(ui->actionSimple_View,SIGNAL(toggled(bool)),SLOT(simplev_toogled()));
    QObject::connect(model,SIGNAL(thumbUpdate(QModelIndex)),SLOT(thumbUpdate(QModelIndex)));
    QObject::connect(QApplication::clipboard(),SIGNAL(changed(QClipboard::Mode)),this,SLOT(clipboardChanged()));
    QObject::connect(this,SIGNAL(copyProgressFinished(int,QStringList)),this,SLOT(progressFinished(int,QStringList)));
    QObject::connect(model,SIGNAL(dragDropPaste(const QMimeData *, QString, QStringList)),this,SLOT(pasteLauncher(const QMimeData *, QString, QStringList)));
    QObject::connect(ui->actionEdit_File,SIGNAL(activated()),SLOT(EditFile()));
    QObject::connect(ui->actionText_Editor,SIGNAL(activated()),SLOT(RunEditor2()));
    QObject::connect(back_bt,SIGNAL(clicked()),SLOT(goBack()));
    QObject::connect(forward_bt,SIGNAL(clicked()),SLOT(goForward()));
    QObject::connect(ui->actionThumbnail_view,SIGNAL(toggled(bool)),SLOT(tv_toogled()));
    QObject::connect(ui->actionCustom_actions,SIGNAL(triggered()),SLOT(editCustomActions()));
    QObject::connect(ui->actionMake_SymLink,SIGNAL(triggered()),SLOT(mkSymLink()));
    QObject::connect(model,SIGNAL(directoryLoaded(QString)),SLOT(dirLoaded(QString)));
    QObject::connect(ui->action_2,SIGNAL(triggered()),SLOT(EditHexFile()));
    QObject::connect(ui->actionSelect_by_pattern,SIGNAL(triggered()),SLOT(selectByPtr()));
    QObject::connect(ui->actionClear_selection,SIGNAL(triggered()),SLOT(clearSelection()));
    QObject::connect(ui->actionSelect_All,SIGNAL(triggered()),SLOT(selectAll()));
    QObject::connect(ui->actionCheck_for_updates,SIGNAL(triggered()),SLOT(checkForUpdates()));
    QObject::connect(ui->actionClear_clipboard,SIGNAL(triggered()),SLOT(clearClipboard()));
}
void MainWindow::treeMode_toogled()
{
    if (ui->actionTree_Mode->isChecked())
        FileView->setTreeMode(true);
    else {
        FileView->collapseAll();
        FileView->setTreeMode(false);
    }
    refreshview();
}
void MainWindow::clearClipboard()
{
    QApplication::clipboard()->clear();
}

void MainWindow::dirLoaded(QString sPath)
{
    Q_UNUSED(sPath);
    loadthumbs();
}

void MainWindow::simplev_toogled()
{
    if (ui->actionSimple_View->isChecked()) {
        FileView->hideColumn(1);
        FileView->hideColumn(2);
        FileView->hideColumn(3);
        FileView->hideColumn(4);
        FileView->header()->setHidden(true);
    }
    else {
        FileView->header()->setHidden(false);
        FileView->showColumn(1);
        FileView->showColumn(2);
        FileView->showColumn(3);
        FileView->showColumn(4);
    }
}
void MainWindow::tv_toogled()
{
    if (ui->actionThumbnail_view->isChecked()) {
        model->setPicMode(true);
    } else {
        model->setPicMode(false);
    }
}

void MainWindow::SetPath(QString sPath,bool remember)
{
    FileView->setRootIndex(modell->mapFromSource(model->index(sPath)));
    FileView->setCurrentIndex(modell->mapFromSource(model->index(sPath)));
    if(remember) {
    future.clear();
    history.push(currentPath);
    }
    LocationRefresh();
}

void MainWindow::refreshview()
{
    SetPath(currentPath,false);
}

void MainWindow::scrollcurrent()
{
    if(model->filePath(modell->mapToSource(FileView->currentIndex())) != currentPath)
        FileView->scrollTo(FileView->currentIndex());
}
void MainWindow::deleteFile()
{
    QModelIndexList selList;
    QSettings settings;
    bool yesToAll;
    if(settings.value("Main/AskToDel",true).toBool())
    {
        yesToAll = false;
    }
    else
    {
        yesToAll = true;
    }
    QModelIndexList proxyList;
    if(FileView->selectionModel()->selectedRows(0).count()) proxyList = FileView->selectionModel()->selectedRows(0);
    else proxyList = FileView->selectionModel()->selectedIndexes();

    foreach(QModelIndex proxyItem, proxyList)
        selList.append(modell->mapToSource(proxyItem));

bool ok = false;
bool confirm = true;

//if(settings.value("confirmDelete").isNull())					//not defined yet
//{
//    if(QMessageBox::question(this,tr("Delete confirmation"),tr("Do you want to confirm all delete operations?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) confirm = 1;
//    else confirm = 0;
//    settings->setValue("confirmDelete",confirm);
//}
//else confirm = settings->value("confirmDelete").toBool();


for(int i = 0; i < selList.count(); ++i)
{
    QFileInfo file(model->filePath(selList.at(i)));
    if(file.filePath() == currentPath) return;

    if(file.isWritable())
    {
        if(file.isSymLink()) ok = QFile::remove(file.filePath());
        else
        {
            if(yesToAll == false)
            {
                if(confirm)
                {
                    int ret = QMessageBox::information(this,tr("Warning !"),tr("Are you sure you want to delete <p><b>\"") + file.filePath() + "</b>?",QMessageBox::Yes | QMessageBox::No | QMessageBox::YesToAll);
                    if(ret == QMessageBox::YesToAll) yesToAll = true;
                    if(ret == QMessageBox::No) return;
                }
            }
            DFileEngine fi;
            ok = fi.remove(model->filePath(selList.at(i)));
        }
    }
    else if(file.isSymLink()) ok = QFile::remove(file.filePath());
}

if(!ok) QMessageBox::information(this,tr("Failed"),tr("Could not delete some items...do you have the right permissions?"));

return;
}
void MainWindow::layoutLock_toogled()
{
    if (ui->actionLock_layout->isChecked()) {
        ui->mainToolBar->setMovable(false);
        ui->locationbar->setMovable(false);
        ui->opToolbar->setMovable(false);
    }
    else {
        ui->mainToolBar->setMovable(true);
        ui->locationbar->setMovable(true);
        ui->opToolbar->setMovable(true);
    }
}

void MainWindow::slothidefiles()
{
    QModelIndexList proxyList;
    if(FileView->selectionModel()->selectedRows(0).count()) proxyList = FileView->selectionModel()->selectedRows(0);
    else proxyList = FileView->selectionModel()->selectedIndexes();


    if(hide_bt->isChecked() == false)
    {
        foreach(QModelIndex proxyItem, proxyList)
            if(model->fileInfo(modell->mapToSource(proxyItem)).isHidden()) FileView->selectionModel()->select(proxyItem,QItemSelectionModel::Deselect);
        while(QFileInfo(currentPath).isHidden())
        {
            GoUp();
        }
        modell->setFilterRegExp("no");
        completerModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    }
    else {
        modell->setFilterRegExp("");
        completerModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
    }
    modell->invalidate();

}
void MainWindow::ViewActivated()
{
    Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();
    if(mods == Qt::ControlModifier || mods == Qt::ShiftModifier) return;
    openFile();
}
void MainWindow::goForward()
{
    if (future.count()>0)
    {
        history.push(currentPath);
        SetPath(future.pop(),false);
    }
}
void MainWindow::goBack()
{
    if (history.count()>0)
    {
        future.push(currentPath);
        SetPath(history.pop(),false);
    }
}

void MainWindow::EditHexFile()
{
    QModelIndexList items;
    if(FileView->selectionModel()->selectedRows(0).count()) items = FileView->selectionModel()->selectedRows(0);
    else items = FileView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, items){
        if(!model->isDir(modell->mapToSource(index))) {
           QString path = model->filePath(modell->mapToSource(index));
           RunHexEditor(path);
        }
    }
}

void MainWindow::EditFile()
{
    QModelIndexList items;
    if(FileView->selectionModel()->selectedRows(0).count()) items = FileView->selectionModel()->selectedRows(0);
    else items = FileView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, items){
        if(!model->isDir(modell->mapToSource(index))) {
           QString path = model->filePath(modell->mapToSource(index));
           RunEditor(path);
        }
    }
}
void MainWindow::openFile()
{
    QModelIndexList items;
    if(model->isDir(modell->mapToSource(FileView->currentIndex()))) {
        SetPath(model->filePath(modell->mapToSource(FileView->currentIndex())));
    } else {
        if(FileView->selectionModel()->selectedRows(0).count()) items = FileView->selectionModel()->selectedRows(0);
        else items = FileView->selectionModel()->selectedIndexes();

        foreach(QModelIndex index, items) {
            if(model->isDesktop(modell->mapToSource(index))&&model->isDesktopMode()) {
                DesktopApp app;
                if(app.init(model->filePath(modell->mapToSource(index)))) {
                    if(app.isURL()) {
                       QString path = app.url();
                       if(path.startsWith("file://")) path.remove("file://");
                       if(QFile(path).exists() && QFileInfo(path).isDir()) {
                           SetPath(path);
                           return;
                        }
                    }
                    app.launch();
                    return;
                }
            }
            if(!model->isDir(modell->mapToSource(index))) QDesktopServices::openUrl( QUrl("file:///"+model->filePath(modell->mapToSource(index))));
        }
    }
}

void MainWindow::tabsTop_toogled()
{
    if(ui->actionTabs_on_top->isChecked() == false) {
        tabs->setShape(QTabBar::RoundedSouth);
        if(!ui->verticalLayout->isEmpty()) ui->verticalLayout->removeWidget(tabs);
        ui->gridLayout->addWidget(tabs);
    } else {
        tabs->setShape(QTabBar::RoundedNorth);
        if(!ui->gridLayout->isEmpty()) ui->gridLayout->removeWidget(tabs);
        ui->verticalLayout->addWidget(tabs);
    }
}
//Run file function
void MainWindow::runFile()
{
    QProcess *myProcess = new QProcess(this);
    myProcess->startDetached(model->filePath(modell->mapToSource(FileView->currentIndex())));
}
void MainWindow::scrollToBottom()
{
    FileView->scrollToBottom();
}
void MainWindow::scrollToTop()
{
    FileView->scrollToTop();
}
//Edit item function
void MainWindow::RenameFile()
{
    FileView->edit(FileView->currentIndex());
}
//Context menu event
void MainWindow::ContextMenu(QPoint pos)
{
    contextmenu *fbMenu = new contextmenu;
    QObject::connect(fbMenu, SIGNAL(createFolderTriggered()), this, SLOT(MakeDir()));
    QObject::connect(fbMenu, SIGNAL(deleteTriggered()), this, SLOT(deleteFile()));
    QObject::connect(fbMenu, SIGNAL(renameTriggered()), this, SLOT(RenameFile()));
    QObject::connect(fbMenu, SIGNAL(createFileTriggered()), this, SLOT(MakeFile()));
    QObject::connect(fbMenu, SIGNAL(openTabTriggered()), this, SLOT(addNewTab()));
    QObject::connect(fbMenu, SIGNAL(openTriggered()), this, SLOT(openFile()));
    QObject::connect(fbMenu, SIGNAL(execFileTriggered()), this, SLOT(runFile()));
    QObject::connect(fbMenu, SIGNAL(infoFileTriggered()), this, SLOT(InfoBoxRun()));
    QObject::connect(fbMenu, SIGNAL(copyTriggered()), this, SLOT(copyFile()));
    QObject::connect(fbMenu, SIGNAL(pasteTriggered()), this, SLOT(pasteClipboard()));
    QObject::connect(fbMenu, SIGNAL(cutTriggered()), this, SLOT(cutFile()));
    readFileTemplates();
    QPoint globalPos = FileView->viewport()->mapToGlobal(pos);
    QList<QAction*> actions;
    QFileInfo fi = model->fileInfo(modell->mapToSource(FileView->selectionModel()->currentIndex()));
    fbMenu->setPasteEnabled(pasteEnabled);
    if(!fi.isDir()) {
        actions = customActions->values(fi.suffix());
        fbMenu->fbOtherMenu->addActions(actions);
        foreach(QMenu* parent, customMenus->values(curIndex.suffix())) {
            fbMenu->addMenu(parent);
        }
        foreach(QMenu* parent, customMenus->values("*")) {
            fbMenu->addMenu(parent);
        }
        actions = (customActions->values("*"));
        fbMenu->fbOtherMenu->addActions(actions);
    } else {
        foreach(QMenu* parent, customMenus->values("*")) {
            fbMenu->addMenu(parent);
        }
        actions = customActions->values("*");
        fbMenu->fbOtherMenu->addActions(actions);
        foreach(QMenu* parent, customMenus->values("folder")) {
            fbMenu->addMenu(parent);
        }
        actions = customActions->values(fi.fileName());               //specific folder
        actions.append(customActions->values(fi.canonicalPath()));    //children of $parent
        actions.append(customActions->values("folder"));                    //all folders
        if(actions.count()) {
            fbMenu->fbOtherMenu->addActions(actions);
        }
    }
    if(!FileTemplatesAction.isEmpty())
        fbMenu->fbNewMenu->addActions(FileTemplatesAction);

    fbMenu->setNewFolderEnabled(true);
    if(fi.isExecutable()&&!fi.isDir()) {
        fbMenu->setExecHide(true);
    } else {
        fbMenu->setExecHide(false);
    }
    if(fi.filePath() != currentPath&&fi.isDir()) {
        fbMenu->openTabsetHide(true);
    } else {
        fbMenu->openTabsetHide(false);
    }
    if(model->filePath(modell->mapToSource(FileView->indexAt(pos))).length()==0) {
        FileView->clearSelection();
        SetPath(currentPath);
    }
    QAction* selectedItem =  fbMenu->exec(globalPos);

    if (selectedItem) {
        // something was chosen, do stuff
       //qDebug() << "test" << selectedItem->text();

    } else {
        // nothing was chosen
    }
    FileTemplatesAction.clear();
    delete fbMenu;
}
//Go function for go bt
void MainWindow::slotgo()
{
    QString sPath = location->text();
    if(sPath.startsWith("~")) sPath.replace("~",QDir::homePath());
    QDir dir(sPath);
    QFile file(sPath);
    if(dir.exists()) {
        SetPath(sPath);
    }
    else if(sPath =="%GOUP%") {
        GoUp();
    }
    else if(sPath == "%EXIT%") {
        QApplication::exit();
    }
    else if(sPath == "%HOME%") {
        GoHome();
    }
    else if(sPath == "%ROOT%") {
        GoRoot();
    }
    else if(sPath == "%TEMP%") {
        SetPath(QDir::tempPath());
    }
    else if(sPath == "%ICONS%") {
        icondlg *icons = new icondlg("All icons");
        icons->exec();
        delete icons;
    }
    else if(sPath == "%DRIVES%") {
        goDrives();
    }
    else if(sPath == "%ERROR%") {
        error("There is simple error number 1");
    }
    else if(sPath.startsWith("http://") | sPath.startsWith("https://")) {
        QDesktopServices::openUrl(QUrl(sPath));
    }
    else if(file.exists()) {
        QDesktopServices::openUrl(QUrl("file:///"+model->filePath(modell->mapToSource(modell->mapFromSource(model->index(sPath))))));
    }
    else {
        ui->statusBar->showMessage(tr("This path does not exists"),3000);
    }
}
void MainWindow::selectByPtr()
{
    bool ok;
    QString pattern = QInputDialog::getText(this, tr("Select by pattern"),
                                            tr("Pattern:"), QLineEdit::Normal,
                                            "", &ok);

    if(ok && !pattern.isEmpty()) {
        QRegExp rx;
        rx.setPattern(pattern);
        rx.setPatternSyntax(QRegExp::Wildcard);
        QModelIndexList items, selList;
        items = model->dirIndexes();

        foreach(QModelIndex theItem,items) {
            if(rx.exactMatch(model->fileName(theItem)))
                selList.append(modell->mapFromSource(theItem));
        }
        if(!selList.isEmpty()) {
            FileView->selectionModel()->clearSelection();
            foreach(QModelIndex selItem,selList) {
                FileView->selectionModel()->select(selItem,QItemSelectionModel::Select | QItemSelectionModel::Rows);
            }
        }
    }
}
//Make symlink function
void MainWindow::mkSymLink()
{
    QFile file(model->filePath(modell->mapToSource(FileView->currentIndex())));
    if (!QFileInfo(currentPath).isWritable()) {
        ui->statusBar->showMessage(tr("Read only...cannot create Symlink"),5000);
        return;
    }
    if(file.fileName() == currentPath) return;
    bool ok;
    QString str = QInputDialog::getText(this, tr("Name of SymLink"),
                                              tr("Name:"), QLineEdit::Normal,
                                              model->fileName(modell->mapToSource(FileView->currentIndex())), &ok);
    if (ok && !str.isEmpty()) {
#ifdef Q_OS_UNIX
    file.link(currentPath+QDir::separator()+str);
#endif
#ifdef Q_OS_WIN
    file.link(currentPath+QDir::separator()+str.append(".lnk"));
#endif
    }
    refreshview();
}
//Change path to Drives list
//Not avaiable for Win now
void MainWindow::goDrives()
{
#ifdef Q_OS_LINUX
    SetPath("/media");
#endif

#ifdef Q_OS_MAC
    SetPath("/Volumes");
#endif
#ifdef Q_OS_WIN
#endif
}
//Error dialog function
void MainWindow::error(QString text)
{
    QErrorMessage msg;
    msg.showMessage(text);
    msg.exec();
}
//Run dialog for edit custom action
void MainWindow::editCustomActions()
{
    //remove all custom actions from list because we will add them all again below.
    foreach(QAction *action, *actionList)
        if(customActions->values().contains(action)) {
            actionList->removeOne(action);
            delete action;
        }

    QList<QMenu*> temp = customMenus->values();

    foreach(QMenu* menu, temp)
        delete menu;

    customActions->clear();
    customMenus->clear();

    customActionsDialog dlg;
    dlg.exec();
    readCustomActions();
}
//Make file function
bool MainWindow::MakeFile()
{
    QModelIndex fileIndex;

    if(!QFileInfo(currentPath).isWritable()) {
        ui->statusBar->showMessage(tr("Read only...cannot create file"),5000);
        return false;
    }
    int num = 0;
    QString name;

    do {
        num++;
        name = QString(tr("new_file%1")).arg(num);
    }
    while (model->hasItem(name));


    QFile temp(currentPath + QDir::separator() + name);
    if(!temp.open(QIODevice::WriteOnly)) return false;
    QFileInfo tmpInfo(temp);
    temp.close();
    fileIndex = modell->mapFromSource(model->index(tmpInfo.absoluteFilePath()));
    FileView->selectionModel()->setCurrentIndex(fileIndex,QItemSelectionModel::ClearAndSelect);
    FileView->edit(fileIndex);
    return true;
}
//Make dir function
bool MainWindow::MakeDir()
{
    QModelIndex newDir;

    if(!QFileInfo(currentPath).isWritable())
    {
        ui->statusBar->showMessage(tr("Read only...cannot create folder"),5000);
        return false;
    }
    int num = 0;
    QString name;

    do
    {
        num++;
        name = QString(tr("new_folder%1")).arg(num);
    }
    while(model->hasItem(name));

    newDir = modell->mapFromSource(model->mkdir(model->index(currentPath),name));
    FileView->selectionModel()->setCurrentIndex(newDir,QItemSelectionModel::ClearAndSelect);

    FileView->edit(newDir);
    return true;

}
//Event filter for view and loacation text
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
 {
     if (obj == FileView) {
         if (event->type() == QEvent::KeyPress) {
             QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
             if(keyEvent->key() == Qt::Key_Backspace)
             {
                 goBack();
                 return true;
             }
             else
             {
                 return false;
             }
         } else {
             return false;
         }
     }
     else if(obj == location) {
         if (event->type() == QEvent::KeyPress) {
             QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
             if(keyEvent->key() == Qt::Key_Return)
             {
                 slotgo();
                 return true;
             }
             else
             {
                 return false;
             }
         } else {
             return false;
         }
     } else {
         // pass the event on to the parent class
         return QMainWindow::eventFilter(obj, event);
     }
 }
void MainWindow::FeedBack()
{
     QDesktopServices::openUrl(QUrl("mailto:denimnumber1@gmail.com?subject=Dino feedback&body=My text"));
}

void MainWindow::selectAll()
{
    FileView->selectAll();
}

void MainWindow::clearSelection()
{
    FileView->selectionModel()->clearSelection();
}

//Zoom out icons in view
void MainWindow::ZoomOut()
{
    if (icosize != 15) {
       icosize -= 5;
       FileView->setIconSize(QSize(icosize, icosize));
    }
}
//Zoom in icons in view
void MainWindow::ZoomIn()
{
    if (icosize != 120) {
       icosize += 5;
       FileView->setIconSize(QSize(icosize, icosize));
    }
}
//Read settings from ini file
void MainWindow::readSettings()
{
    QSettings settings;
    this->resize(settings.value("Main/size", QSize(600, 400)).toSize());
    icosize = settings.value("Main/icosize",35).toInt();
    ToolBarIconSize = settings.value("Main/toolbaricosize",24).toInt();
    FileView->setIconSize(QSize(icosize,icosize));
    hide_bt->setChecked(settings.value("Main/hiddenMode",0).toBool());
    ui->actionTabs_on_top->setChecked(settings.value("Main/tabontop",0).toBool());
    ui->actionLock_layout->setChecked(settings.value("Main/locklayout",0).toBool());
    FileView->header()->restoreState(settings.value("Main/header").toByteArray());
    term = settings.value("Main/terminal").toString();
    ui->actionThumbnail_view->setChecked(settings.value("Main/thumbs",1).toBool());

    // Set tool bar icon size
    ui->opToolbar->setIconSize(QSize(ToolBarIconSize,ToolBarIconSize));
    ui->locationbar->setIconSize(QSize(ToolBarIconSize,ToolBarIconSize));
    ui->mainToolBar->setIconSize(QSize(ToolBarIconSize,ToolBarIconSize));

    if(!settings.value("Main/windowState").isNull()&&settings.value("Main/windowState").isValid()) {
        this->restoreState(settings.value("Main/windowState").toByteArray(),1);
    }
    FileView->setAnimated(settings.value("Main/animatedtree",true).toBool());
    if(settings.value("Main/hideOwnCol",false).toBool() == true)
        FileView->hideColumn(4);
    else
        FileView->showColumn(4);

    model->setDesktopMode(settings.value("Main/DesktopMode",true).toBool());
    ui->actionTree_Mode->setChecked(settings.value("Main/TreeMode",false).toBool());
    model->setCacheMode(settings.value("Main/CacheMode",true).toBool());


    slothidefiles();
    tabsTop_toogled();
    layoutLock_toogled();
    tv_toogled();
    treeMode_toogled();
    //Load theme
    if(!settings.value("Main/style","").toString().isEmpty()) {
        loadTheme(settings.value("Main/style").toString());
    } else {
        qApp->setStyleSheet("");
    }

}
//Write settings to ini file
void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("Main/size", this->size());
    settings.setValue("Main/icosize",icosize);
    settings.setValue("Main/hiddenMode",hide_bt->isChecked());
    settings.setValue("Main/tabontop",ui->actionTabs_on_top->isChecked());
    settings.setValue("Main/locklayout",ui->actionLock_layout->isChecked());
    settings.setValue("Main/windowState", this->saveState(1));
    settings.setValue("Main/header",FileView->header()->saveState());
    settings.setValue("Main/thumbs",ui->actionThumbnail_view->isChecked());
    settings.setValue("Main/TreeMode",ui->actionTree_Mode->isChecked());
}
void MainWindow::loadTheme(QString themeFile)
{
    QString themePath = qApp->applicationDirPath()+QDir::separator()+"themes"+QDir::separator();
    QFile file(themeFile);
    if (!file.exists()) return;
    file.open(QFile::ReadOnly);
    QString style = file.readAll();
    qApp->setStyleSheet(style);
}
//Change path to root. On Unix "/"
void MainWindow::GoRoot()
{
    SetPath(QDir::rootPath());
}
//Show dialog about dino
void MainWindow::AboutDlg()
{
    QMessageBox::about(this, tr("About"), tr(
        "Version %1"
        "<p><b>Dino file manager</b><br>"
        "(C) 2012 Copyright Dino project.<br>"
        "<p>Dino - simple file manager based on the Qt.<br>Official website <a href=\"https://sourceforge.net/projects/dfm/\">Dino project</a>."
        ).arg(QCoreApplication::applicationVersion()));
}
void MainWindow::LocationRefresh()
{
    QString sPath = model->filePath(modell->mapToSource(FileView->currentIndex()));
    location->setText(sPath);
    currentPath = sPath;
    model->setRootPath(currentPath);
    modell->invalidate();
    tabs->updateTab(sPath);
    if (currentPath == "/") // Only on *nix systems
        up_bt->setEnabled(false);
    else
        up_bt->setEnabled(true);
}
void MainWindow::loadthumbs()
{
    QModelIndexList items;

    for(int x = 0; x < model->rowCount(model->index(currentPath)); ++x)
        items.append(model->index(x,0,model->index(currentPath)));
        QtConcurrent::run(model,&DFileSystemModel::loadThumbs,items);

}
void MainWindow::thumbUpdate(QModelIndex index)
{
    FileView->update(modell->mapFromSource(index));
}
//Change path to Home folder
void MainWindow::GoHome()
{
    SetPath(QDir::homePath());
}
//Change path to the apps folder. Only on OSX
void MainWindow::GoApps()
{
    SetPath(QDesktopServices::storageLocation(QDesktopServices::ApplicationsLocation));
}
//Change path to Music folder
void MainWindow::GoMusic()
{
    SetPath(QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
}
//Change path to Movies folder
void MainWindow::GoMovies()
{
    SetPath(QDesktopServices::storageLocation(QDesktopServices::MoviesLocation));

}
//Change path to pictures folder
void MainWindow::GoPictures()
{
    SetPath(QDesktopServices::storageLocation(QDesktopServices::PicturesLocation));

}
//Change path to docs folder
void MainWindow::GoDocs()
{
    SetPath(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation));
}
//Slot emited when the clipbard data changed
void MainWindow::clipboardChanged()
{
    if(QApplication::clipboard()->mimeData()->hasUrls())
        setPaste(true);
    else {
        model->clearCutItems();
        setPaste(false);
    }
}
// Change path to desktop folder
void MainWindow::GoDesktop()
{
    SetPath(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));
}
// Change path to parent dir
void MainWindow::GoUp()
{
   QString sPath = model->filePath(modell->mapToSource(modell->mapFromSource(model->index(currentPath).parent())));
   SetPath(sPath);
}
void MainWindow::recurseFolder(QString path, QString parent, QStringList *list)
{
    QDir dir(path);
    QStringList files = dir.entryList(QDir::AllEntries | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

    for(int i = 0; i < files.count(); i++)
    {
        if(QFileInfo(files.at(i)).isDir()) recurseFolder(files.at(i),parent + QDir::separator() + files.at(i),list);
        else list->append(parent + QDir::separator() + files.at(i));
    }
}
bool MainWindow::cutCopyFile(QString source, QString dest, qint64 totalSize, bool cut)
{
    QFile in(source);
    QFile out(dest);

    if(out.exists()) return 1;  //file exists, don't do anything

    if (dest.length() > 50) dest = "/.../" + dest.split(QDir::separator()).last();

    in.open(QFile::ReadOnly);
    out.open(QFile::WriteOnly);

    char block[4096];
    qint64 total = in.size();
    qint64 steps = total >> 7;        //shift right 7, same as divide 128, much faster
    qint64 interTotal = 0;

    while(!in.atEnd())
    {
        if(progress->result() == 1) break;                 //cancelled

        qint64 inBytes = in.read(block, sizeof(block));
        out.write(block, inBytes);
        interTotal += inBytes;

        if(interTotal > steps)
        {
            emit updateCopyProgress(interTotal,totalSize,dest);
            interTotal = 0;
        }
    }

    emit updateCopyProgress(interTotal,totalSize,dest);

    out.close();
    in.close();

    if(out.size() != total) return 0;
    if(cut) QFile::remove(source);  //if file is cut remove the source
    return 1;
}
void MainWindow::pasteClipboard()
{
    QString newPath;
    QStringList cutList;
    QFileInfo fi = model->fileInfo(modell->mapToSource(FileView->currentIndex()));

    if(fi.isDir()) newPath = fi.filePath();
    else newPath = currentPath;

    //check list of files that are to be cut
    QFile tempFile(QDir::tempPath() + QDir::separator()+ "dino.temp");
    if(tempFile.exists())
    {
        QModelIndexList list;
        tempFile.open(QIODevice::ReadOnly);
        QDataStream out(&tempFile);
        out >> cutList;
        tempFile.close();
    }

    pasteLauncher(QApplication::clipboard()->mimeData(), newPath, cutList);
}
void MainWindow::pasteLauncher(const QMimeData * data, QString newPath, QStringList cutList)
{
    QList<QUrl> files = data->urls();

    if(!QFile(files.at(0).path()).exists())
    {
        QMessageBox::information(this,tr("No paste for you!"),tr("File no longer exists!"));
        setPaste(0);
        return;
    }

    int replace = 0;
    QStringList completeList;
    QString baseName = QFileInfo(files.at(0).toLocalFile()).path();

    if(newPath != baseName)			    //only if not in same directory, otherwise we will do 'Copy(x) of'
    {
    	foreach(QUrl file, files)
        {
            QFileInfo temp(file.toLocalFile());

            if(temp.isDir() && QFileInfo(newPath + QDir::separator() + temp.fileName()).exists())     //merge or replace?
            {
                QMessageBox message(QMessageBox::Question,tr("Existing folder"),QString("<b>%1</b><p>Already exists!<p>What do you want to do?")
                    .arg(newPath + QDir::separator() + temp.fileName()),QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

                message.button(QMessageBox::Yes)->setText(tr("Merge"));
                message.button(QMessageBox::No)->setText(tr("Replace"));

                int merge = message.exec();
                if(merge == QMessageBox::Cancel) return;
                if(merge == QMessageBox::Yes) recurseFolder(temp.filePath(),temp.fileName(),&completeList);
                else model->remove(model->index(newPath + QDir::separator() + temp.fileName()));
            }
            else completeList.append(temp.fileName());
        }

        foreach(QString file, completeList)
        {
            QFileInfo temp(newPath + QDir::separator() + file);
            if(temp.exists())
            {
                QFileInfo orig(baseName + QDir::separator() + file);
                if(replace != QMessageBox::YesToAll && replace != QMessageBox::NoToAll)
                        replace = QMessageBox::question(0,tr("Replace"),QString("Do you want to replace:<p><b>%1</p><p>Modified: %2<br>Size: %3 bytes</p><p>with:<p><b>%4</p><p>Modified: %5<br>Size: %6 bytes</p>")
                                .arg(temp.filePath()).arg(temp.lastModified().toString()).arg(temp.size())
                                .arg(orig.filePath()).arg(orig.lastModified().toString()).arg(orig.size()),QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll | QMessageBox::Cancel);

                if(replace == QMessageBox::Cancel) return;
                if(replace == QMessageBox::Yes || replace == QMessageBox::YesToAll)
                model->remove(model->index(temp.filePath()));
            }

        }
    }

    QString title;
    if(cutList.count() == 0) title = tr("Copying...");
    else title = tr("Moving...");

    progress = new ProgressDialog(title);
    connect(this,SIGNAL(updateCopyProgress(qint64, qint64, QString)),progress,SLOT(update(qint64, qint64, QString)));

    FileView->selectionModel()->clear();
    QtConcurrent::run(this,&MainWindow::pasteFile, files, newPath, cutList);
}
void MainWindow::progressFinished(int ret,QStringList newFiles)
{
    if(progress != 0)
    {
        progress->close();
        delete progress;
        progress = 0;
    }

    if(newFiles.count())
    {
        qApp->processEvents();              //make sure notifier has added new files to the model

        if(QFileInfo(newFiles.first()).path() == currentPath)       //highlight new files if visible
        {
            foreach(QString item, newFiles)
                FileView->selectionModel()->select(modell->mapFromSource(model->index(item)),QItemSelectionModel::Select);
        }

        FileView->scrollTo(modell->mapFromSource(model->index(newFiles.first())),QAbstractItemView::EnsureVisible);


        if(QFile(QDir::tempPath() + QDir::separator()+ "dino.temp").exists()) QApplication::clipboard()->clear();

        clearCutItems();
        refreshview();
    }

    if(ret == 1) QMessageBox::information(this,tr("Failed"),tr("Paste failed...do you have write permissions?"));
    if(ret == 2) QMessageBox::warning(this,tr("Too big!"),tr("There is not enough space on the destination drive!"));
}
bool MainWindow::pasteFile(QList<QUrl> files,QString newPath, QStringList cutList)
{
    bool ok = true;
    QStringList newFiles;

    if(!QFileInfo(newPath).isWritable() || newPath == QDir(files.at(0).toLocalFile()).path())        //quit if folder not writable
    {
        emit copyProgressFinished(1,newFiles);
        return 0;
    }

    //get total size in bytes
    qint64 total = 1;
    foreach(QUrl url, files)
    {
        QFileInfo file = url.path();
        if(file.isFile()) total += file.size();
        else
        {
            QDirIterator it(url.path(),QDir::AllEntries | QDir::System | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
            while (it.hasNext())
            {
                it.next();
            total += it.fileInfo().size();
            }
        }
    }

    //check available space on destination before we start
    struct statfs info;
    statfs(newPath.toLocal8Bit(), &info);

    if((qint64) info.f_bavail*info.f_bsize < total)
    {
        emit copyProgressFinished(2,newFiles);
        return 0;
    }


    //main loop
    for(int i = 0; i < files.count(); ++i)
    {
        if(progress->result() == 1)			//cancelled
        {
            emit copyProgressFinished(0,newFiles);
            return 1;
        }

        QFileInfo temp(files.at(i).toLocalFile());
        QString destName = temp.fileName();

        if(temp.path() == newPath)			// only do 'Copy(x) of' if same folder
        {
            int num = 1;
            while(QFile(newPath + QDir::separator() + destName).exists())
            {
                destName = QString("Copy (%1) of %2").arg(num).arg(temp.fileName());
                num++;
            }
        }

        destName = newPath + QDir::separator() + destName;
        QFileInfo dName(destName);

        if(!dName.exists() || dName.isDir())
        {
            newFiles.append(destName);				    //keep a list of new files so we can select them later

            if(cutList.contains(temp.filePath()))			    //cut action
            {
                if (temp.isFile()) //files
                {
                    QFSFileEngine file(temp.filePath());
                    if(!file.rename(destName))			    //rename will fail if across different filesystem, so use copy/remove method
                        ok = cutCopyFile(temp.filePath(), destName, total, true);
                }
                else
                {
                    ok = QFile(temp.filePath()).rename(destName);
                    if(!ok)	//file exists or move folder between different filesystems, so use copy/remove method
                    {
                        if(temp.isDir())
                        {
                            ok = true;
                            copyFolder(temp.filePath(), destName, total, true);
                            model->clearCutItems();
                        }
                        //file already exists, don't do anything
                    }
                }
            }
            else
            {
                if(temp.isDir())
                    copyFolder(temp.filePath(),destName,total,false);
                else
                    ok = cutCopyFile(temp.filePath(), destName, total, false);
            }
        }
    }

    emit copyProgressFinished(0,newFiles);
    return 1;
}
bool MainWindow::copyFolder(QString sourceFolder, QString destFolder, qint64 total, bool cut)
{
    QDir sourceDir(sourceFolder);
    QDir destDir(QFileInfo(destFolder).path());
    QString folderName = QFileInfo(destFolder).fileName();

    bool ok = true;

    if(!QFileInfo(destFolder).exists()) destDir.mkdir(folderName);
    destDir = QDir(destFolder);

    QStringList files = sourceDir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

    for(int i = 0; i < files.count(); i++)
    {
        QString srcName = sourceDir.path() + QDir::separator() + files[i];
        QString destName = destDir.path() + QDir::separator() + files[i];
        if(!cutCopyFile(srcName, destName, total, cut)) ok = false;     //don't remove source folder if all files not cut

        if(progress->result() == 1) return 0;                           //cancelled
    }

    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);

    for(int i = 0; i < files.count(); i++)
    {
        if(progress->result() == 1) return 0;			    //cancelled

        QString srcName = sourceDir.path() + QDir::separator() + files[i];
        QString destName = destDir.path() + QDir::separator() + files[i];
        copyFolder(srcName, destName, total, cut);
    }

    //remove source folder if all files moved ok
    if(cut && ok) sourceDir.rmdir(sourceFolder);
    return ok;
}
void MainWindow::cutFile()
{
    QModelIndexList selList;
    QStringList fileList;
    if(FileView->selectionModel()->selectedRows(0).count()) selList = FileView->selectionModel()->selectedRows(0);
    else selList = FileView->selectionModel()->selectedIndexes();

    foreach(QModelIndex item, selList)
        fileList.append(model->filePath(modell->mapToSource(item)));

    clearCutItems();
    model->addCutItems(fileList);

    //save a temp file to allow pasting in a different instance
    QFile tempFile(QDir::tempPath() + QDir::separator() +"dino.temp");
    tempFile.open(QIODevice::WriteOnly);
    QDataStream out(&tempFile);
    out << fileList;
    tempFile.close();

    QApplication::clipboard()->setMimeData(modell->mimeData(selList));

    FileView->selectionModel()->clear();
}
void MainWindow::clearCutItems()
{
    //this refreshes existing items, sizes etc but doesn't re-sort
    model->clearCutItems();
//    model->update();

    return;
}
void MainWindow::checkForUpdates()
{
    DNetwork *net = new DNetwork();
    QObject::connect(net,SIGNAL(latestVersionMsg()),SLOT(showMsgDinoLatest()));
    QObject::connect(net,SIGNAL(developmentVersionMsg()),SLOT(showMsgDinoDevel()));
    QObject::connect(net,SIGNAL(needUpdate(double)),SLOT(needDinoUpdate(double)));

    net->checkForUpdates();

    delete net;
}
void MainWindow::showMsgDinoLatest()
{
    QMessageBox::information(this,tr("Dino!"),tr("You have the latest version of the Dino"),QMessageBox::Ok);
}
void MainWindow::showMsgDinoDevel()
{
    QMessageBox::information(this,tr("Dino!"),tr("You have the development version of the Dino"),QMessageBox::Ok);
}
void MainWindow::needDinoUpdate(double version)
{
    QMessageBox::information(this,tr("Dino!"),tr("You have not the latest version %1. <a href=\"https://dfm.sourceforge.net/\">Update Dino!</a>").arg(version),QMessageBox::Ok);
}

void MainWindow::copyFile()
{
    QModelIndexList selList;
    if(FileView->selectionModel()->selectedRows(0).count()) selList = FileView->selectionModel()->selectedRows(0);
    else selList = FileView->selectionModel()->selectedIndexes();

    if(selList.count() == 0) return;

    clearCutItems();

    QStringList text;
    foreach(QModelIndex item,selList)
        text.append(model->filePath(modell->mapToSource(item)));

    QApplication::clipboard()->setText(text.join("\n"),QClipboard::Selection);
    QApplication::clipboard()->setMimeData(modell->mimeData(selList));
}
bool viewSortProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(this->filterRegExp().isEmpty()) return true;

    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    DFileSystemModel* fileModel = qobject_cast<DFileSystemModel*>(sourceModel());

    if(fileModel->fileInfo(index0).isHidden()) return false;
    else return true;
}
void MainWindow::setPaste(bool a)
{
     pasteEnabled = a;
     paste_bt->setEnabled(a);
     ui->actionPaste->setEnabled(a);
}
//Read custom actions from file
void MainWindow::readCustomActions()
{
    QSettings settings;
    customMenus = new QMultiHash<QString,QMenu*>;

    settings.beginGroup("customActions");
    QStringList keys = settings.childKeys();

    for(int i = 0; i < keys.count(); ++i)
    {
        QStringList temp(settings.value(keys.at(i)).toStringList());

        // temp.at(0) - FileType
        // temp.at(1) - Text
        // temp.at(2) - Icon
        // temp.at(3) - Command

        QAction *tempAction = new QAction(QIcon::fromTheme(temp.at(2)),temp.at(1),this);
        runCommandMappper->setMapping(tempAction,temp.at(3));
        connect(tempAction, SIGNAL(triggered()), runCommandMappper, SLOT(map()));

        actionList->append(tempAction);

        QStringList types = temp.at(0).split(",");

        foreach(QString type,types)
        {
            QStringList children(temp.at(1).split(" / "));
            if(children.count() > 1) {
                QMenu * parent = 0;
                tempAction->setText(children.at(1));

                foreach(QMenu *subMenu,customMenus->values(type))
                    if(subMenu->title() == children.at(0)) parent = subMenu;

                if(parent == 0) {
                    parent = new QMenu(children.at(0));
                    customMenus->insert(type,parent);
                }

                parent->addAction(tempAction);
                customActions->insert("null",tempAction);
            } else
                customActions->insert(type,tempAction);
        }
    }
    settings.endGroup();
}
void MainWindow::actionMapper(QString cmd)
{
    QModelIndexList selList;
    QStringList temp;
    QFileInfo file = model->fileInfo(modell->mapToSource(FileView->currentIndex()));

    if(file.isDir())
        cmd.replace("%n",file.fileName().replace(" ","\\"));
    else
        cmd.replace("%n",file.baseName().replace(" ","\\"));

    if(FileView->selectionModel()->selectedRows(0).count()) selList = FileView->selectionModel()->selectedRows(0);
    else selList = FileView->selectionModel()->selectedIndexes();


    cmd.replace("~",QDir::homePath());


    //process any input tokens
    int pos = 0;
    while(pos >= 0)
    {
        pos = cmd.indexOf("%i",pos);
        if(pos != -1) {
            pos += 2;
            QString var = cmd.mid(pos,cmd.indexOf(" ",pos) - pos);
            QString input = QInputDialog::getText(this,tr("Input"), var, QLineEdit::Normal);
            if(input.isNull()) return;              //cancelled
            else cmd.replace("%i" + var,input);
        }
    }


    foreach(QModelIndex index,selList)
        temp.append(model->fileName(modell->mapToSource(index)).replace(" ","\\"));

    cmd.replace("%f",temp.join(" "));

    temp.clear();

    foreach(QModelIndex index,selList)
        temp.append(model->filePath(modell->mapToSource(index)).replace(" ","\\"));

    cmd.replace("%F",temp.join(" "));

    temp = cmd.split(" ");

    QString exec = temp.at(0);
    temp.removeAt(0);

    temp.replaceInStrings("\\","\ ");

    QProcess *customProcess = new QProcess();
    customProcess->setWorkingDirectory(currentPath);

    connect(customProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(customActionError(QProcess::ProcessError)));
    connect(customProcess,SIGNAL(finished(int)),this,SLOT(customActionFinished(int)));

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(exec.at(0) == '|') {
        exec.remove(0,1);
        env.insert("DFM", "1");
        customProcess->setProcessEnvironment(env);
    }

    customProcess->start(exec,temp);
}
void MainWindow::customActionError(QProcess::ProcessError error)
{
    QProcess* process = qobject_cast<QProcess*>(sender());
    QMessageBox::warning(this,tr("Error"),process->errorString());
    customActionFinished(0);
}
void MainWindow::customActionFinished(int ret)
{
    QProcess* process = qobject_cast<QProcess*>(sender());

    if(process->processEnvironment().contains("DFM")) {
        QString output = process->readAllStandardError();
        if(!output.isEmpty()) QMessageBox::warning(this,tr("Error - Custom action"),output);

        output = process->readAllStandardOutput();
        if(!output.isEmpty()) QMessageBox::information(this,tr("Output - Custom action"),output);
    }

    clearCutItems();                //updates file sizes
    process->deleteLater();
}
bool viewSortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    DFileSystemModel* fsModel = dynamic_cast<DFileSystemModel*>(sourceModel());

    if((fsModel->isDir(left) && !fsModel->isDir(right)))
        return sortOrder() == Qt::AscendingOrder;
    else if(!fsModel->isDir(left) && fsModel->isDir(right))
        return sortOrder() == Qt::DescendingOrder;

    if(left.column() == 1) {
        if(fsModel->size(left) > fsModel->size(right)) return true;
        else return false;
    }
    else if(left.column() == 3)          //date
    {
        if(fsModel->fileInfo(left).lastModified() > fsModel->fileInfo(right).lastModified()) return true;
        else return false;
    }

    return QSortFilterProxyModel::lessThan(left,right);
}

QString formatSize(qint64 num)
{
    QString total;
    const qint64 kb = 1024;
    const qint64 mb = 1024 * kb;
    const qint64 gb = 1024 * mb;
    const qint64 tb = 1024 * gb;

    if (num >= tb) total = QString("%1TB").arg(QString::number(qreal(num) / tb, 'f', 2));
    else if(num >= gb) total = QString("%1GB").arg(QString::number(qreal(num) / gb, 'f', 2));
    else if(num >= mb) total = QString("%1MB").arg(QString::number(qreal(num) / mb, 'f', 1));
    else if(num >= kb) total = QString("%1KB").arg(QString::number(qreal(num) / kb,'f', 1));
    else total = QString("%1 bytes").arg(num);

    return total;
}


