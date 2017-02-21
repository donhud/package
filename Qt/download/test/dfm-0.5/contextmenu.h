#ifndef contextmenu_H
#define contextmenu_H

#include <QMenu>

class contextmenu : public QMenu
{
    Q_OBJECT
public:
    explicit contextmenu(QWidget *parent = 0);
    ~contextmenu();
    //! Other menu for CustomActions and future pluginsystem
    QMenu *fbOtherMenu;
    //! New menu within the context menu. Includes actions like cretion of folders
    QMenu *fbNewMenu;
    void openTabsetHide(bool a);

    void addcontextmenuAction(QAction *action);

    //! Adds a separator to the conext menu
    /*!
      Adds a separator to the conext menu of files in the file browser
      */
    void addcontextmenuSeparator();

    //! Removes an action from the conext menu
    /*!
      Removes an action from the conext menu of files in the file browser
      \param action Action to be removed from the context menu
      */
    void removeFromcontextmenu(QAction *action);

    //! Returns context menu's list of actions
    /*!
      Returns a list with the context menu actions
      */
    QList <QAction *> contextmenuActions();

    //! Enables/disables New Folder option in the context menu
    /*!
      Enables/disables New Folder option in the context menu. Normally is enabled when the selected file (current index of the data model) is a directory
      */
    void setNewFolderEnabled(bool);
    //! Enables/disables Paste option in the context menu
    /*!
      Enables/disables Paste option in the context menu. Normally is enabled when there is something in the clipboard
      and disabled after pasting the content
      */
    void setPasteEnabled(bool);

    void setExecHide(bool a);

    QAction *cut;


private:
    //! Action for opening a file or directory
    QAction *open;
    //! Action for deleting a file or directory
    QAction *del;
    //! Action for copying a file or directory
    QAction *copy;
    //! Action for cutting a file or directory
    //! Action for pasting a file or directory
    QAction *paste;
    //! Action for renaming a file or directory
    QAction *rename;
    //! Action for creating a directory
    QAction *addFolder;
    //! Action for open in new tab
    QAction *OpenIntab;
    //! Action for creating a file
    QAction *addFile;
    //! Action for execute file
    QAction *execFile;
    //! Action fot infobox
    QAction *infoFile;

signals:
    //! This signal is emitted when the run menu option is triggered
    void execFileTriggered();
    //! This signal is emitted when the open menu option is triggered
    void openTriggered();
    //! This signal is emitted when the copy menu option is triggered
    void openTabTriggered();
    //! This signal is emitted when the openTab option is triggered
    void copyTriggered();
    //! This signal is emitted when the cut menu option is triggered
    void cutTriggered();
    //! This signal is emitted when the paste menu option is triggered
    void pasteTriggered();
    //! This signal is emitted when the delete menu option is triggered
    void deleteTriggered();
    //! This signal is emitted when the rename menu option is triggered
    void renameTriggered();
    //! This signal is emitted when the New Folder menu option is triggered
    void createFolderTriggered();
    //! This signal is emitted when the New File menu option is triggered
    void createFileTriggered();
    //! This signal is emitted when the Info menu option is triggered
    void infoFileTriggered();

public slots:

};

#endif // contextmenu_H
