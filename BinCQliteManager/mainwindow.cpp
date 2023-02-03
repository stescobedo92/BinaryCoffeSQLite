#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "findreplacedialog.h"
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QPrinter>
#include <QPrintDialog>
#include <QSqlQueryModel>

//alias for QTreeWidgetItem component
using TreeItem = QTreeWidgetItem;
using ListItem = QListWidgetItem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqlQueryModel = new QSqlQueryModel(this);
    ui->tableView->setModel(sqlQueryModel);
    ui->centralwidget->layout()->setContentsMargins(0,0,0,0);

    connect(ui->treeWidget, &BinCQLiteTreeWidget::newTable, [&](){
        auto itm = ui->treeWidget->currentItem();
        if(itm == nullptr){
             QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
             return;
        }

        auto pather = itm->parent();
        if(pather != nullptr) {
           QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
           return;
        }
    });

    connect(ui->treeWidget, &BinCQLiteTreeWidget::dropDataBase, [&](){
        auto itm = ui->treeWidget->currentItem();
        if(itm == nullptr){
             QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
             return;
        }

        auto pather = itm->parent();
        if(pather != nullptr) {
           QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
           return;
        }
        ui->textEdit->clear();

        delete itm;
    });

    connect(ui->treeWidget, &BinCQLiteTreeWidget::selectDataScript, [&](){
        auto itm = ui->treeWidget->currentItem();
        if(itm == nullptr){
             QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
             return;
        }

        auto pather = itm->parent();
        if(pather == nullptr) {
           QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
           return;
        }
        ui->textEdit->clear();
        ui->textEdit->setPlainText(QString("SELECT * FROM %1").arg(itm->text(0)));
    });

    connect(ui->treeWidget, &BinCQLiteTreeWidget::dropTable, [&](){
        auto itm = ui->treeWidget->currentItem();
        if(itm == nullptr){
             QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one data base"));
             return;
        }

        auto pather = itm->parent();
        if(pather == nullptr) {
           QMessageBox::warning(this,QString("Attention"), QString("This function is only permit when is selected one table"));
           return;
        }
        ui->textEdit->clear();
        ui->textEdit->setPlainText(QString("DROP TABLE %1").arg(itm->text(0)));
    });
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
    mDataBase.setDatabaseName(databaseName);

    if(!mDataBase.open()) {
        QMessageBox::critical(this,QString("Error"), QString("Error: The data base %1 could not be open").arg(databaseNameInfo.fileName()));
        return;
    }
    else {
        QSqlQuery query;
        query.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
        while(query.next()) {
            auto tableItem = new TreeItem;
            tableItem->setIcon(0, QIcon(""));
            tableItem->setText(0, query.value(0).toString());
            databaseItem->addChild(tableItem);
        }
        ui->treeWidget->addTopLevelItem(databaseItem);
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
    auto sqlQuery = ui->textEdit->toPlainText();
    if(sqlQuery.startsWith("select", Qt::CaseInsensitive)) {
        sqlQueryModel->setQuery(sqlQuery);
    }
    else if(sqlQuery.startsWith("create table", Qt::CaseInsensitive)) {
        QSqlQuery qry;
        if(!qry.exec(sqlQuery)) {
            ui->listWidget->addItem(new ListItem(QIcon(""),sqlQuery));
            return;
        }
        ui->listWidget->addItem(new ListItem(QIcon(""),sqlQuery));

        auto currentDataBase = mDataBase.databaseName();
        int i, tam = ui->treeWidget->topLevelItemCount();
        for(i=0; i < tam; ++i) {
          if(ui->treeWidget->topLevelItem(i)->text(0).toLower() == currentDataBase.toLower()) {
              break;
          }
        }

        auto baseItem = ui->treeWidget->topLevelItem(i);
        auto createTable = QString("create table ");

        if(sqlQuery.contains("if not exists", Qt::CaseInsensitive))
            createTable = QString("create table if not exists ");

        int firstPosition = createTable.size();
        int secondPosition = sqlQuery.indexOf("(", firstPosition);
        auto table = sqlQuery.mid(firstPosition, secondPosition - firstPosition);
        table = table.mid(0, table.indexOf(" "));

        tam = baseItem->childCount();
        for(i=0; i < tam; ++i) {
          if(baseItem->child(i)->text(0).toLower() == table.toLower()) {
              return;
          }
        }

        auto tableItem = new TreeItem;
        tableItem->setIcon(0, QIcon(""));
        tableItem->setText(0, table);
        baseItem->addChild(tableItem);
    }
    else if(sqlQuery.startsWith("drop table", Qt::CaseInsensitive)) {
        QSqlQuery qry;
        if(!qry.exec(sqlQuery)) {
            ui->listWidget->addItem(new ListItem(QIcon(""),sqlQuery));
            return;
        }
        ui->listWidget->addItem(new ListItem(QIcon(""),sqlQuery));

        auto currentDataBase = mDataBase.databaseName();
        int i, tam = ui->treeWidget->topLevelItemCount();
        for(i=0; i < tam; ++i) {
          if(ui->treeWidget->topLevelItem(i)->text(0) == currentDataBase) {
              break;
          }
        }

        auto baseItem = ui->treeWidget->topLevelItem(i);
        tam = baseItem->childCount();
        auto droptable = QString("drop table");
        auto table = sqlQuery.mid(droptable.size());
        table = table.mid(1);

        for(i = 0; i < tam; ++i) {
            if(baseItem->child(i)->text(0).toLower() == table.toLower())
                break;
        }

        baseItem->removeChild(baseItem->child(i));
    }
    else {
        QSqlQuery qry;
        if(!qry.exec(sqlQuery)) {
            ui->listWidget->addItem(new ListItem(QIcon(""),sqlQuery));
            return;
        }
        ui->listWidget->addItem(new ListItem(QIcon(""),sqlQuery));
    }
}


void MainWindow::on_actionPreferences_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"Binary Coffee Sqlite Manager", "Example test");
}


void MainWindow::on_actionFind_and_Replace_triggered()
{
    FindReplaceDialog findReplaceDialog(this);
    findReplaceDialog.setTextEdit(ui->textEdit);
    findReplaceDialog.exec();
}


void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    if(index.parent().isValid())
        return;

    QString databaBaseName = index.data().toString();
    mDataBase.setDatabaseName(databaBaseName);
    if(!mDataBase.open()) {
       QMessageBox::information(this,QString("Saved"), QString("The data base %1 was saved").arg(databaBaseName));
    }
}

