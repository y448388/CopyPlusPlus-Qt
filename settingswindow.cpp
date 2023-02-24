#include "settingswindow.h"
#include "mainwindow.h"
#include "qevent.h"
#include "ui_settingswindow.h"
#include <QSettings>

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow(parent),
                                                  ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    setFixedSize(228, 275);

    updateText();

    QSettings settings;
    QString curLang = MainWindow::getInstance()->languageName.key(settings.value("language", "zh_CN").toString());
    ui->languageList->setCurrentText(curLang);

    // 函数指针
    void (QComboBox::*currentIndexChanged)(const QString &) = &QComboBox::currentIndexChanged;
    connect(ui->languageList, currentIndexChanged, MainWindow::getInstance(), &MainWindow::updateLanguageByName);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
    event->accept();
}

void SettingsWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        // 感觉没啥用
        ui->retranslateUi(this);

        // 更新文本，用于翻译
        updateText();
    }

    QMainWindow::changeEvent(event);
}

void SettingsWindow::updateText()
{
    setWindowTitle(tr("设置"));

    ui->languageLable->setText(tr("语言"));

    QComboBox *list = ui->languageList;
    QStringList allLanguages = MainWindow::getInstance()->languageName.keys();

    if (list->count() == 0) {
        for (int i = 0; i < allLanguages.count(); ++i) {
            list->addItem(tr(allLanguages[i].toUtf8()));
        }
    } else {
        for (int i = 0; i < allLanguages.count(); ++i) {
            list->setItemText(i, tr(allLanguages[i].toUtf8()));
        }
    }
}
