/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Jun 29 16:28:29 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionNew_folder;
    QAction *actionRemove;
    QAction *actionHidden_files;
    QAction *actionGo_to_url;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionScroll_to_top;
    QAction *actionScroll_to_bottom;
    QAction *actionAdd_new_tab;
    QAction *actionRefresh;
    QAction *actionRun_terminal;
    QAction *actionTabs_on_top;
    QAction *actionLock_layout;
    QAction *actionScroll_to_selected_item;
    QAction *actionSimple_View;
    QAction *actionEdit_File;
    QAction *actionText_Editor;
    QAction *actionThumbnail_view;
    QAction *actionCustom_actions;
    QAction *actionMake_SymLink;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionTree_Mode;
    QAction *actionSettings;
    QAction *actionHex_Editor;
    QAction *action_2;
    QAction *actionSelect_by_pattern;
    QAction *actionClear_selection;
    QAction *actionSelect_All;
    QAction *actionCheck_for_updates;
    QAction *actionClear_clipboard;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuGo_to;
    QMenu *menuView;
    QMenu *menu_Extras;
    QMenu *menuEdit;
    QStatusBar *statusBar;
    QToolBar *opToolbar;
    QToolBar *mainToolBar;
    QToolBar *locationbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(668, 422);
        MainWindow->setWindowTitle(QString::fromUtf8("Dino"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/files/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionNew_folder = new QAction(MainWindow);
        actionNew_folder->setObjectName(QString::fromUtf8("actionNew_folder"));
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        actionRemove->setIconVisibleInMenu(true);
        actionHidden_files = new QAction(MainWindow);
        actionHidden_files->setObjectName(QString::fromUtf8("actionHidden_files"));
        actionHidden_files->setCheckable(false);
        actionGo_to_url = new QAction(MainWindow);
        actionGo_to_url->setObjectName(QString::fromUtf8("actionGo_to_url"));
        actionGo_to_url->setCheckable(false);
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        actionScroll_to_top = new QAction(MainWindow);
        actionScroll_to_top->setObjectName(QString::fromUtf8("actionScroll_to_top"));
        actionScroll_to_bottom = new QAction(MainWindow);
        actionScroll_to_bottom->setObjectName(QString::fromUtf8("actionScroll_to_bottom"));
        actionAdd_new_tab = new QAction(MainWindow);
        actionAdd_new_tab->setObjectName(QString::fromUtf8("actionAdd_new_tab"));
        actionRefresh = new QAction(MainWindow);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        actionRun_terminal = new QAction(MainWindow);
        actionRun_terminal->setObjectName(QString::fromUtf8("actionRun_terminal"));
        actionTabs_on_top = new QAction(MainWindow);
        actionTabs_on_top->setObjectName(QString::fromUtf8("actionTabs_on_top"));
        actionTabs_on_top->setCheckable(true);
        actionTabs_on_top->setChecked(false);
        actionLock_layout = new QAction(MainWindow);
        actionLock_layout->setObjectName(QString::fromUtf8("actionLock_layout"));
        actionLock_layout->setCheckable(true);
        actionScroll_to_selected_item = new QAction(MainWindow);
        actionScroll_to_selected_item->setObjectName(QString::fromUtf8("actionScroll_to_selected_item"));
        actionSimple_View = new QAction(MainWindow);
        actionSimple_View->setObjectName(QString::fromUtf8("actionSimple_View"));
        actionSimple_View->setCheckable(true);
        actionEdit_File = new QAction(MainWindow);
        actionEdit_File->setObjectName(QString::fromUtf8("actionEdit_File"));
        actionText_Editor = new QAction(MainWindow);
        actionText_Editor->setObjectName(QString::fromUtf8("actionText_Editor"));
        actionThumbnail_view = new QAction(MainWindow);
        actionThumbnail_view->setObjectName(QString::fromUtf8("actionThumbnail_view"));
        actionThumbnail_view->setCheckable(true);
        actionThumbnail_view->setChecked(true);
        actionCustom_actions = new QAction(MainWindow);
        actionCustom_actions->setObjectName(QString::fromUtf8("actionCustom_actions"));
        actionMake_SymLink = new QAction(MainWindow);
        actionMake_SymLink->setObjectName(QString::fromUtf8("actionMake_SymLink"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionTree_Mode = new QAction(MainWindow);
        actionTree_Mode->setObjectName(QString::fromUtf8("actionTree_Mode"));
        actionTree_Mode->setCheckable(true);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionHex_Editor = new QAction(MainWindow);
        actionHex_Editor->setObjectName(QString::fromUtf8("actionHex_Editor"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        actionSelect_by_pattern = new QAction(MainWindow);
        actionSelect_by_pattern->setObjectName(QString::fromUtf8("actionSelect_by_pattern"));
        actionClear_selection = new QAction(MainWindow);
        actionClear_selection->setObjectName(QString::fromUtf8("actionClear_selection"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        actionCheck_for_updates = new QAction(MainWindow);
        actionCheck_for_updates->setObjectName(QString::fromUtf8("actionCheck_for_updates"));
        actionClear_clipboard = new QAction(MainWindow);
        actionClear_clipboard->setObjectName(QString::fromUtf8("actionClear_clipboard"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 668, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuGo_to = new QMenu(menuBar);
        menuGo_to->setObjectName(QString::fromUtf8("menuGo_to"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menu_Extras = new QMenu(menuBar);
        menu_Extras->setObjectName(QString::fromUtf8("menu_Extras"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        opToolbar = new QToolBar(MainWindow);
        opToolbar->setObjectName(QString::fromUtf8("opToolbar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, opToolbar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        locationbar = new QToolBar(MainWindow);
        locationbar->setObjectName(QString::fromUtf8("locationbar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, locationbar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuGo_to->menuAction());
        menuBar->addAction(menu_Extras->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_folder);
        menuFile->addAction(actionMake_SymLink);
        menuFile->addSeparator();
        menuFile->addAction(actionEdit_File);
        menuFile->addAction(action_2);
        menuFile->addSeparator();
        menuFile->addAction(actionRemove);
        menuFile->addSeparator();
        menuFile->addAction(actionRun_terminal);
        menuFile->addAction(actionAdd_new_tab);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuFile->addSeparator();
        menuHelp->addAction(actionCheck_for_updates);
        menuView->addAction(actionGo_to_url);
        menuView->addSeparator();
        menuView->addAction(actionTabs_on_top);
        menuView->addAction(actionSimple_View);
        menuView->addAction(actionThumbnail_view);
        menuView->addAction(actionTree_Mode);
        menuView->addAction(actionLock_layout);
        menuView->addSeparator();
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_out);
        menuView->addSeparator();
        menuView->addAction(actionScroll_to_top);
        menuView->addAction(actionScroll_to_selected_item);
        menuView->addAction(actionScroll_to_bottom);
        menuView->addSeparator();
        menuView->addAction(actionRefresh);
        menu_Extras->addAction(actionText_Editor);
        menu_Extras->addAction(actionHex_Editor);
        menu_Extras->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect_All);
        menuEdit->addAction(actionSelect_by_pattern);
        menuEdit->addAction(actionClear_selection);
        menuEdit->addSeparator();
        menuEdit->addAction(actionClear_clipboard);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCustom_actions);
        menuEdit->addAction(actionSettings);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(activated()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainWindow", "F10", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionNew_folder->setText(QApplication::translate("MainWindow", "New folder", 0, QApplication::UnicodeUTF8));
        actionNew_folder->setShortcut(QApplication::translate("MainWindow", "F6", 0, QApplication::UnicodeUTF8));
        actionRemove->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        actionHidden_files->setText(QApplication::translate("MainWindow", "Hidden files", 0, QApplication::UnicodeUTF8));
        actionHidden_files->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0, QApplication::UnicodeUTF8));
        actionGo_to_url->setText(QApplication::translate("MainWindow", "Go to url", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setText(QApplication::translate("MainWindow", "zoom in", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setText(QApplication::translate("MainWindow", "zoom out", 0, QApplication::UnicodeUTF8));
        actionScroll_to_top->setText(QApplication::translate("MainWindow", "Scroll to top", 0, QApplication::UnicodeUTF8));
        actionScroll_to_top->setShortcut(QApplication::translate("MainWindow", "Ctrl+Up", 0, QApplication::UnicodeUTF8));
        actionScroll_to_bottom->setText(QApplication::translate("MainWindow", "Scroll to bottom", 0, QApplication::UnicodeUTF8));
        actionScroll_to_bottom->setShortcut(QApplication::translate("MainWindow", "Ctrl+Down", 0, QApplication::UnicodeUTF8));
        actionAdd_new_tab->setText(QApplication::translate("MainWindow", "Add new tab", 0, QApplication::UnicodeUTF8));
        actionRefresh->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        actionRefresh->setShortcut(QApplication::translate("MainWindow", "F5", 0, QApplication::UnicodeUTF8));
        actionRun_terminal->setText(QApplication::translate("MainWindow", "Run terminal", 0, QApplication::UnicodeUTF8));
        actionRun_terminal->setShortcut(QApplication::translate("MainWindow", "F2", 0, QApplication::UnicodeUTF8));
        actionTabs_on_top->setText(QApplication::translate("MainWindow", "Tabs on top", 0, QApplication::UnicodeUTF8));
        actionLock_layout->setText(QApplication::translate("MainWindow", "Lock layout", 0, QApplication::UnicodeUTF8));
        actionScroll_to_selected_item->setText(QApplication::translate("MainWindow", "Scroll to selected item", 0, QApplication::UnicodeUTF8));
        actionScroll_to_selected_item->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSimple_View->setText(QApplication::translate("MainWindow", "Simple View", 0, QApplication::UnicodeUTF8));
        actionEdit_File->setText(QApplication::translate("MainWindow", "Edit File", 0, QApplication::UnicodeUTF8));
        actionEdit_File->setShortcut(QApplication::translate("MainWindow", "F4", 0, QApplication::UnicodeUTF8));
        actionText_Editor->setText(QApplication::translate("MainWindow", "Text Editor", 0, QApplication::UnicodeUTF8));
        actionThumbnail_view->setText(QApplication::translate("MainWindow", "Thumbnail view", 0, QApplication::UnicodeUTF8));
        actionCustom_actions->setText(QApplication::translate("MainWindow", "Custom actions", 0, QApplication::UnicodeUTF8));
        actionMake_SymLink->setText(QApplication::translate("MainWindow", "Make SymLink", 0, QApplication::UnicodeUTF8));
        actionMake_SymLink->setShortcut(QApplication::translate("MainWindow", "F7", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
        actionTree_Mode->setText(QApplication::translate("MainWindow", "Tree Mode", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionHex_Editor->setText(QApplication::translate("MainWindow", "Hex Editor", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("MainWindow", "Edit file with hex editor", 0, QApplication::UnicodeUTF8));
        actionSelect_by_pattern->setText(QApplication::translate("MainWindow", "Select by pattern", 0, QApplication::UnicodeUTF8));
        actionClear_selection->setText(QApplication::translate("MainWindow", "Clear selection", 0, QApplication::UnicodeUTF8));
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", 0, QApplication::UnicodeUTF8));
        actionCheck_for_updates->setText(QApplication::translate("MainWindow", "Check for updates...", 0, QApplication::UnicodeUTF8));
        actionClear_clipboard->setText(QApplication::translate("MainWindow", "Clear clipboard", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuGo_to->setTitle(QApplication::translate("MainWindow", "&Go to", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0, QApplication::UnicodeUTF8));
        menu_Extras->setTitle(QApplication::translate("MainWindow", "&Extras", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        opToolbar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        mainToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        locationbar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
