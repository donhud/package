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
#include "texteditor.h"
#include <QtGui>


TextEditor::TextEditor(QString path)
{
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    setWindowIcon(QIcon(":/files/logo.png"));
    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
    if(!path.isEmpty()&&!path.isNull())
    {
        setCurrentFile(path);
        loadFile(path);
    }
    else
    {
        setCurrentFile("");
    }
    setUnifiedTitleAndToolBarOnMac(true);
    highlighter = new HighlighterCpp(textEdit->document());

}
TextEditor::~TextEditor()
{
    delete highlighter;
    delete HiglightAct;
    delete newAct;
    delete exitAct;
    delete openAct;
    delete saveAct;
    delete saveAsAct;
    delete findAct;
    delete cutAct;
    delete pasteAct;
    delete copyAct;
    delete clrFindRes;
}

void TextEditor::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}
void TextEditor::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        textEdit->undo();
        setCurrentFile("");
    }
}
void TextEditor::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}
bool TextEditor::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}
bool TextEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}
void TextEditor::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}
void TextEditor::createActions()
{
    newAct = new QAction(QIcon::fromTheme("document-new",QIcon(":/images/new.png")), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon::fromTheme("document-open",QIcon(":/images/open.png")), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon::fromTheme("document-save",QIcon(":/images/save.png")), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon::fromTheme("edit-cut",QIcon(":/images/cut.png")), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon::fromTheme("edit-copy",QIcon(":/images/copy.png")), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon::fromTheme("edit-paste",QIcon(":/images/paste.png")), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    findAct = new QAction(QIcon::fromTheme("edit-find"),tr("Find"), this);
    findAct->setShortcuts(QKeySequence::Find);
    findAct->setStatusTip(tr("Find text"));
    connect(findAct,SIGNAL(triggered()), this, SLOT(findText()));

    clrFindRes = new QAction(tr("Clear found results"), this);
    clrFindRes->setStatusTip(tr("Clear found results"));
    connect(clrFindRes,SIGNAL(triggered()), this, SLOT(clrresults()));

    HiglightAct = new QAction(tr("Higlihter"),this);
    HiglightAct->setStatusTip(tr("Enable Higlighter"));
    HiglightAct->setCheckable(true);
    connect(HiglightAct, SIGNAL(toggled(bool)), this, SLOT(hl_toogled()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
}
void TextEditor::findText()
{
    bool ok;
    QString str = QInputDialog::getText(this, tr("Find"),
                                             tr("Text:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (ok && !str.isEmpty())
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        if(!textEdit->isReadOnly())
        {
             textEdit->moveCursor(QTextCursor::Start);
             QColor color = QColor(Qt::yellow).lighter(130);
             while(textEdit->find(str))
                {
                    QTextEdit::ExtraSelection extra;

                    extra.format.setBackground(color);
                    extra.cursor = textEdit->textCursor();

                    extraSelections.append(extra);

                }

            }
         textEdit->setExtraSelections(extraSelections);
    }
}
void TextEditor::hl_toogled()
{
    bool a = HiglightAct->isChecked();
    highlighter->setDocument(a ? textEdit->document() : 0);
}
void TextEditor::clrresults()
{
    textEdit->extraSelections().clear();
    QList<QTextEdit::ExtraSelection> extraSelections;
    textEdit->setExtraSelections(extraSelections);
}
void TextEditor::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(findAct);
    editMenu->addAction(clrFindRes);
    editMenu->addAction(HiglightAct);

    menuBar()->addSeparator();

}
void TextEditor::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->setObjectName("FileToolBar");

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->setObjectName("EditToolBar");
}
void TextEditor::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
void TextEditor::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("Editor/pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("Editor/size", QSize(400, 400)).toSize();
    if(!settings.value("Editor/state").isNull())
    {
        restoreState(settings.value("Editor/state").toByteArray(),1);
    }
    resize(size);
    move(pos);
}
void TextEditor::writeSettings()
{
    QSettings settings;
    settings.setValue("Editor/pos", pos());
    settings.setValue("Editor/size", size());
    settings.setValue("Editor/state",saveState(1));
}
bool TextEditor::maybeSave()
{
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Editor"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}
void TextEditor::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Editor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}
bool TextEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}
void TextEditor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
QString TextEditor::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

