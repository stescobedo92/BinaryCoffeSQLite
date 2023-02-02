#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QPrinter>
#include <QPrintDialog>

//alias for QTreeWidgetItem component
using TreeItem = QTreeWidgetItem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mDataBase = QSqlDatabase::addDatabase("QSQLITE");
    ui->centralwidget->layout()->setContentsMargins(0,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_Data_Base_triggered()
{
    auto databaseName = QFileDialog::getOpenFileName(this, QString("Open data base"), QDir::currentPath(), QString("Data base (*.db);;"));

    if(databaseName.isEmpty())
        return;

    auto databaseNameInfo = QFileInfo(databaseName);
    auto databaseItem = new TreeItem;
    databaseItem->setIcon(0, QIcon(""));
    databaseItem->setText(0, databaseNameInfo.fileName());
    ui->treeWidget->addTopLevelItem(databaseItem);
    mDataBase.setDatabaseName(databaseName);

    if(!mDataBase.open()) {
        QMessageBox::critical(this,QString("Error"), QString("Error: The data base %1 could not be open").arg(databaseNameInfo.fileName()));
    }
    else {
        QMessageBox::information(this,QString("Openend"), QString("The data base %1 was open").arg(databaseNameInfo.fileName()));
    }

}


void MainWindow::on_actionSave_Data_Base_triggered()
{
    auto saveDatabaseName = QFileDialog::getSaveFileName(this, QString("Save data base"), QDir::currentPath(), QString("Data base (*.db);;"));

    if(saveDatabaseName.isEmpty())
        return;

    auto databaseNameInfo = QFileInfo(saveDatabaseName);
    auto databaseItem = new TreeItem;
    databaseItem->setIcon(0, QIcon(""));
    databaseItem->setText(0, databaseNameInfo.fileName());
    ui->treeWidget->addTopLevelItem(databaseItem);
    mDataBase.setDatabaseName(saveDatabaseName);

    if(!mDataBase.open()) {
        QMessageBox::critical(this,QString("Error"), QString("Error: The data base %1 could not be open").arg(databaseNameInfo.fileName()));
    }
    else {
        QMessageBox::information(this,QString("Saved"), QString("The data base %1 was saved").arg(databaseNameInfo.fileName()));
    }
}


void MainWindow::on_actionOpen_SQL_Script_triggered()
{
    auto saveScript = QFileDialog::getOpenFileName(this, QString("Save script"), QDir::currentPath(), QString("SQL file (*.sql);;"));

    if(saveScript.isEmpty())
        return;

    QFile scriptFile(saveScript);
    if (!scriptFile.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::critical(this,QString("Error"), QString("Error: The script %1 cannot be open").arg(scriptFile.fileName()));
    }
    else {
        QTextStream scripTextStream(&scriptFile);
        QMessageBox::information(this,QString("Saved"), QString("The script %1 was saved").arg(scriptFile.fileName()));
        ui->textEdit->setText(scripTextStream.readAll());
    }
    scriptFile.close();
}


void MainWindow::on_actionSave_SQL_Script_triggered()
{
    auto openScript = QFileDialog::getSaveFileName(this, QString("Open script"), QDir::currentPath(), QString("SQL file (*.sql);;"));

    if(openScript.isEmpty())
        return;

    QFile scriptFile(openScript);
    if (!scriptFile.open(QIODevice::Text | QIODevice::WriteOnly)) {
        QMessageBox::critical(this,QString("Error"), QString("Error: The script %1 cannot be open").arg(scriptFile.fileName()));
    }
    else {
        QTextStream scripTextStream(&scriptFile);
        scripTextStream << ui->textEdit->toPlainText();
        QMessageBox::information(this,QString("Saved"), QString("The script file %1 was saved").arg(scriptFile.fileName()));
    }
    scriptFile.flush();
    scriptFile.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrintDialog print(this);
    if(print.exec() == QDialog::Rejected)
        return;

    ui->textEdit->print(print.printer());
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

