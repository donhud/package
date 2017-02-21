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
#include <QtGui>

#include "Hmainwindow.h"

/*****************************************************************************/
/* Public methods */
/*****************************************************************************/
HMainWindow::HMainWindow(QString path)
{
    init();
    if(!path.isEmpty() && !path.isNull() && QFile::exists(path)) {
        loadFile(path);
        setCurrentFile(path);
    }
    else
        setCurrentFile("");
}

/*****************************************************************************/
/* Protected methods */
/*****************************************************************************/
void HMainWindow::closeEvent(QCloseEvent *)
{
    writeSettings();
}

/*****************************************************************************/
/* Private Slots */
/*****************************************************************************/

void HMainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"),QDir::homePath());
    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }
}

void HMainWindow::optionsAccepted()
{
    writeSettings();
    readSettings();
}

void HMainWindow::findNext()
{
    searchDialog->findNext();
}

bool HMainWindow::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool HMainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void HMainWindow::saveSelectionToReadableFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save To Readable File"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Dino"),
                                 tr("Cannot write file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
            return;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        file.write(hexEdit->selectionToReadableString().toLatin1());
        QApplication::restoreOverrideCursor();

        statusBar()->showMessage(tr("File saved"), 2000);
    }
}

void HMainWindow::saveToReadableFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save To Readable File"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Dino"),
                                 tr("Cannot write file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
            return;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        file.write(hexEdit->toReadableString().toLatin1());
        QApplication::restoreOverrideCursor();

        statusBar()->showMessage(tr("File saved"), 2000);
    }
}

void HMainWindow::setAddress(int address)
{
    lbAddress->setText(QString("%1").arg(address, 1, 16));
}

void HMainWindow::setOverwriteMode(bool mode)
{
    if (mode)
        lbOverwriteMode->setText(tr("Overwrite"));
    else
        lbOverwriteMode->setText(tr("Insert"));
}

void HMainWindow::setSize(int size)
{
    lbSize->setText(QString("%1").arg(size));
}

void HMainWindow::showOptionsDialog()
{
    optionsDialog->show();
}

void HMainWindow::showSearchDialog()
{
    searchDialog->show();
}

/*****************************************************************************/
/* Private Methods */
/*****************************************************************************/
void HMainWindow::init()
{
    setAttribute(Qt::WA_DeleteOnClose);
    optionsDialog = new OptionsDialog(this);
    connect(optionsDialog, SIGNAL(accepted()), this, SLOT(optionsAccepted()));
    isUntitled = true;

    hexEdit = new QHexEdit;
    setCentralWidget(hexEdit);
    connect(hexEdit, SIGNAL(overwriteModeChanged(bool)), this, SLOT(setOverwriteMode(bool)));
    searchDialog = new SearchDialog(hexEdit, this);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    setUnifiedTitleAndToolBarOnMac(true);
}

void HMainWindow::createActions()
{
    openAct = new QAction(QIcon::fromTheme("document-open"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon::fromTheme("document-save"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    saveReadable = new QAction(tr("Save &Readable..."), this);
    saveReadable->setStatusTip(tr("Save document in readable form"));
    connect(saveReadable, SIGNAL(triggered()), this, SLOT(saveToReadableFile()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered()), hexEdit, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered()), hexEdit, SLOT(redo()));

    saveSelectionReadable = new QAction(tr("&Save Selection Readable..."), this);
    saveSelectionReadable->setStatusTip(tr("Save selection in readable form"));
    connect(saveSelectionReadable, SIGNAL(triggered()), this, SLOT(saveSelectionToReadableFile()));

    findAct = new QAction(tr("&Find/Replace"), this);
    findAct->setShortcuts(QKeySequence::Find);
    findAct->setStatusTip(tr("Show the Dialog for finding and replacing"));
    connect(findAct, SIGNAL(triggered()), this, SLOT(showSearchDialog()));

    findNextAct = new QAction(tr("Find &next"), this);
    findNextAct->setShortcuts(QKeySequence::FindNext);
    findNextAct->setStatusTip(tr("Find next occurrence of the searched pattern"));
    connect(findNextAct, SIGNAL(triggered()), this, SLOT(findNext()));

    optionsAct = new QAction(tr("&Options"), this);
    optionsAct->setStatusTip(tr("Show the Dialog to select applications options"));
    connect(optionsAct, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));
}

void HMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(saveReadable);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(saveSelectionReadable);
    editMenu->addSeparator();
    editMenu->addAction(findAct);
    editMenu->addAction(findNextAct);
    editMenu->addSeparator();
    editMenu->addAction(optionsAct);
}

void HMainWindow::createStatusBar()
{
    // Address Label
    lbAddressName = new QLabel();
    lbAddressName->setText(tr("Address:"));
    statusBar()->addPermanentWidget(lbAddressName);
    lbAddress = new QLabel();
    lbAddress->setFrameShape(QFrame::Panel);
    lbAddress->setFrameShadow(QFrame::Sunken);
    lbAddress->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbAddress);
    connect(hexEdit, SIGNAL(currentAddressChanged(int)), this, SLOT(setAddress(int)));

    // Size Label
    lbSizeName = new QLabel();
    lbSizeName->setText(tr("Size:"));
    statusBar()->addPermanentWidget(lbSizeName);
    lbSize = new QLabel();
    lbSize->setFrameShape(QFrame::Panel);
    lbSize->setFrameShadow(QFrame::Sunken);
    lbSize->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbSize);
    connect(hexEdit, SIGNAL(currentSizeChanged(int)), this, SLOT(setSize(int)));

    // Overwrite Mode Label
    lbOverwriteModeName = new QLabel();
    lbOverwriteModeName->setText(tr("Mode:"));
    statusBar()->addPermanentWidget(lbOverwriteModeName);
    lbOverwriteMode = new QLabel();
    lbOverwriteMode->setFrameShape(QFrame::Panel);
    lbOverwriteMode->setFrameShadow(QFrame::Sunken);
    lbOverwriteMode->setMinimumWidth(70);
    statusBar()->addPermanentWidget(lbOverwriteMode);
    setOverwriteMode(hexEdit->overwriteMode());

    statusBar()->showMessage(tr("Ready"));
}

void HMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
}

void HMainWindow::loadFile(const QString &fileName)
{

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("SDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    hexEdit->setData(file.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void HMainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(610, 460)).toSize();
    move(pos);
    resize(size);

    hexEdit->setAddressArea(settings.value("AddressArea").toBool());
    hexEdit->setAsciiArea(settings.value("AsciiArea").toBool());
    hexEdit->setHighlighting(settings.value("Highlighting").toBool());
    hexEdit->setOverwriteMode(settings.value("OverwriteMode").toBool());
    hexEdit->setReadOnly(settings.value("ReadOnly").toBool());

    hexEdit->setHighlightingColor(settings.value("HighlightingColor").value<QColor>());
    hexEdit->setAddressAreaColor(settings.value("AddressAreaColor").value<QColor>());
    hexEdit->setSelectionColor(settings.value("SelectionColor").value<QColor>());
    hexEdit->setFont(settings.value("WidgetFont").value<QFont>());

    hexEdit->setAddressWidth(settings.value("AddressAreaWidth").toInt());
}

bool HMainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("QHexEdit"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    file.write(hexEdit->data());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void HMainWindow::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = fileName.isEmpty();
    setWindowModified(false);
    setWindowFilePath(curFile);
}

QString HMainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void HMainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

