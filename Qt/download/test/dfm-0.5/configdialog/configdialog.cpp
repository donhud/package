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

#include "configdialog.h"

ConfigDialog::ConfigDialog()
{
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    MainPage = new ConfigurationPage(this);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(MainPage);
//    pagesWidget->addWidget(new UpdatePage);
//    pagesWidget->addWidget(new QueryPage);
    QPushButton *closeButton = new QPushButton(tr("Close"));
    QPushButton *saveButton = new QPushButton(tr("Save"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(writeSettings()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Dino settings"));
}

void ConfigDialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("Configuration"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

//    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
//    updateButton->setIcon(QIcon(":/images/update.png"));
//    updateButton->setText(tr("Update"));
//    updateButton->setTextAlignment(Qt::AlignHCenter);
//    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

//    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
//    queryButton->setIcon(QIcon(":/images/query.png"));
//    queryButton->setText(tr("Query"));
//    queryButton->setTextAlignment(Qt::AlignHCenter);
//    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    resize(QSize(750,500));
    readSettings();

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::writeSettings()
{
    QSettings settings;
    settings.setValue("Main/terminal",MainPage->terminal->text());
    settings.setValue("Main/toolbaricosize",MainPage->toolBarIconSize->value());
    settings.setValue("Main/animatedtree",MainPage->AnimatedTree->isChecked());
    settings.setValue("Main/hideOwnCol",MainPage->hideOwnColumn->isChecked());
    settings.setValue("Main/DesktopMode",MainPage->DesktopMode->isChecked());
    settings.setValue("Main/AskToDel",MainPage->AskToDelete->isChecked());
    settings.setValue("Main/CacheMode",MainPage->enableThumbCache->isChecked());
    settings.setValue("Main/style",MainPage->themeEntry->text());
    close();
}

void ConfigDialog::readSettings()
{
    QSettings settings;
    MainPage->terminal->setText(settings.value("Main/terminal").toString());
    MainPage->toolBarIconSize->setValue(settings.value("Main/toolbaricosize",24).toInt());
    MainPage->AnimatedTree->setChecked(settings.value("Main/animatedtree",true).toBool());
    MainPage->hideOwnColumn->setChecked(settings.value("Main/hideOwnCol",false).toBool());
    MainPage->DesktopMode->setChecked(settings.value("Main/DesktopMode",true).toBool());
    MainPage->AskToDelete->setChecked(settings.value("Main/AskToDel",true).toBool());
    MainPage->enableThumbCache->setChecked(settings.value("Main/CacheMode",true).toBool());
    MainPage->themeEntry->setText(settings.value("Main/style","").toString());
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
ConfigDialog::~ConfigDialog()
{
    delete contentsWidget;
    delete MainPage;
    delete pagesWidget;
}
