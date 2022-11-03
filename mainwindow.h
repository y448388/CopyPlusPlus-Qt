#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qhotkey.h"
#include "qsettings.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *event);

    void ininGui();
    void loadSettings();
    void saveSettings();

    void toggleAutoEnabled();

    void startSetShorcut();

    void setShortcutEnabled(bool status);
    void registerShortcut(const QKeySequence &keySequence);
    void shortcutTriggered();

    void keySequenceEditFinished();
    // void truncateShortcut();

    void pressCtrlC();
#ifdef Q_OS_WIN
    void setClipboardTextWin(QString);
#endif

    void processClipboard();
    void afterChanged();

private:
    bool flag = false;

    Ui::MainWindow *ui;
    QHotkey *hotkey;

    QString settingsIniFile;
    QSettings settings;
};
#endif // MAINWINDOW_H
