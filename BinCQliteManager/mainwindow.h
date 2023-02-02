#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_Data_Base_triggered();

    void on_actionSave_Data_Base_triggered();

    void on_actionOpen_SQL_Script_triggered();

    void on_actionSave_SQL_Script_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionExecute_triggered();

    void on_actionPreferences_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mDataBase;
};
#endif // MAINWINDOW_H
