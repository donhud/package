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
#include "pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Main"));
    QGroupBox *ToolBarGroup = new QGroupBox(tr("Toolbars"));
    QGroupBox *FileViewGroup = new QGroupBox(tr("File view"));


    QLabel *terminalLabel = new QLabel(tr("Default terminal:"));
    terminal = new QLineEdit;
    terminal->setText("terminal");

    QLabel *themeLabel = new QLabel(tr("Theme file:"));
    themeEntry = new QLineEdit;

    QLabel *toolBarLabel = new QLabel(tr("Toolbars icon size:"));
    toolBarIconSize = new QSpinBox;
    toolBarIconSize->setMinimum(16);
    toolBarIconSize->setMaximum(48);

    AnimatedTree = new QCheckBox(tr("Animated tree"));
    hideOwnColumn = new QCheckBox(tr("Hide owner column"));
    DesktopMode = new QCheckBox(tr("Show desktop launchers"));
    AskToDelete = new QCheckBox(tr("Ask for confirmation to delete the files"));
    enableThumbCache = new QCheckBox(tr("Enable thumbnails cache"));

    QGridLayout *MainConfLayout = new QGridLayout;
    MainConfLayout->addWidget(terminalLabel,0,0);
    MainConfLayout->addWidget(terminal,0,1);
    MainConfLayout->addWidget(AskToDelete,1,0);
    MainConfLayout->addWidget(themeLabel,2,0);
    MainConfLayout->addWidget(themeEntry,2,1);

    QGridLayout *ToolBarConfLayout = new QGridLayout;
    ToolBarConfLayout->addWidget(toolBarLabel,0,0);
    ToolBarConfLayout->addWidget(toolBarIconSize,0,1);

    QGridLayout *FileViewConfLayout = new QGridLayout;
    FileViewConfLayout->addWidget(AnimatedTree,0,0);
    FileViewConfLayout->addWidget(hideOwnColumn,1,0);
    FileViewConfLayout->addWidget(DesktopMode,2,0);
    FileViewConfLayout->addWidget(enableThumbCache,3,0);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(MainConfLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *ToolBarsLayout = new QVBoxLayout;
    ToolBarsLayout->addLayout(ToolBarConfLayout);
    ToolBarGroup->setLayout(ToolBarsLayout);

    QVBoxLayout *FileViewLayout = new QVBoxLayout;
    FileViewLayout->addLayout(FileViewConfLayout);
    FileViewGroup->setLayout(FileViewLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    mainLayout->addWidget(ToolBarGroup);
    mainLayout->addWidget(FileViewGroup);
    setLayout(mainLayout);
}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
//    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
//    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
//    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
//    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

//    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

//    QListWidget *packageList = new QListWidget;
//    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
//    qtItem->setText(tr("Qt"));
//    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
//    qsaItem->setText(tr("QSA"));
//    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
//    teamBuilderItem->setText(tr("Teambuilder"));

//    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

//    QVBoxLayout *updateLayout = new QVBoxLayout;
//    updateLayout->addWidget(systemCheckBox);
//    updateLayout->addWidget(appsCheckBox);
//    updateLayout->addWidget(docsCheckBox);
//    updateGroup->setLayout(updateLayout);

//    QVBoxLayout *packageLayout = new QVBoxLayout;
//    packageLayout->addWidget(packageList);
//    packageGroup->setLayout(packageLayout);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(updateGroup);
//    mainLayout->addWidget(packageGroup);
//    mainLayout->addSpacing(12);
//    mainLayout->addWidget(startUpdateButton);
//    mainLayout->addStretch(1);
//    setLayout(mainLayout);
}

QueryPage::QueryPage(QWidget *parent)
    : QWidget(parent)
{
//    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

//    QLabel *nameLabel = new QLabel(tr("Name:"));
//    QLineEdit *nameEdit = new QLineEdit;

//    QLabel *dateLabel = new QLabel(tr("Released after:"));
//    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

//    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
//    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

//    QSpinBox *hitsSpinBox = new QSpinBox;
//    hitsSpinBox->setPrefix(tr("Return up to "));
//    hitsSpinBox->setSuffix(tr(" results"));
//    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
//    hitsSpinBox->setMinimum(1);
//    hitsSpinBox->setMaximum(100);
//    hitsSpinBox->setSingleStep(10);

//    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

//    QGridLayout *packagesLayout = new QGridLayout;
//    packagesLayout->addWidget(nameLabel, 0, 0);
//    packagesLayout->addWidget(nameEdit, 0, 1);
//    packagesLayout->addWidget(dateLabel, 1, 0);
//    packagesLayout->addWidget(dateEdit, 1, 1);
//    packagesLayout->addWidget(releasesCheckBox, 2, 0);
//    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
//    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
//    packagesGroup->setLayout(packagesLayout);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(packagesGroup);
//    mainLayout->addSpacing(12);
//    mainLayout->addWidget(startQueryButton);
//    mainLayout->addStretch(1);
//    setLayout(mainLayout);
}
