#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->layout()->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_Data_Base_triggered()
{

}


void MainWindow::on_actionSave_Data_Base_triggered()
{

}


void MainWindow::on_actionOpen_SQL_Script_triggered()
{

}


void MainWindow::on_actionSave_SQL_Script_triggered()
{

}


void MainWindow::on_actionPrint_triggered()
{

}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionExecute_triggered()
{

}


void MainWindow::on_actionPreferences_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"Binary Coffee Sqlite Manager", "Example test");
}

