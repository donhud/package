#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include "qhexedit.h"
#include "optionsdialog.h"
#include "searchdialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QUndoStack;
QT_END_NAMESPACE

class HMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    HMainWindow(QString path);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    void optionsAccepted();
    void findNext();
    bool save();
    bool saveAs();
    void saveSelectionToReadableFile();
    void saveToReadableFile();
    void setAddress(int address);
    void setOverwriteMode(bool mode);
    void setSize(int size);
    void showOptionsDialog();
    void showSearchDialog();

private:
    void init();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolBars();
    void loadFile(const QString &fileName);
    void readSettings();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void writeSettings();

    QString curFile;
    bool isUntitled;
    
    QMenu *fileMenu;
    QMenu *editMenu;

    QToolBar *fileToolBar;

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *saveReadable;
    QAction *closeAct;
    QAction *exitAct;

    QAction *undoAct;
    QAction *redoAct;
    QAction *saveSelectionReadable;

    QAction *optionsAct;
    QAction *findAct;
    QAction *findNextAct;

    QHexEdit *hexEdit;
    OptionsDialog *optionsDialog;
    SearchDialog *searchDialog;
    QLabel *lbAddress, *lbAddressName;
    QLabel *lbOverwriteMode, *lbOverwriteModeName;
    QLabel *lbSize, *lbSizeName;
};

#endif
