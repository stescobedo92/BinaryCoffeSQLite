#include "bincqlitenewtabledialog.h"
#include "ui_bincqlitenewtabledialog.h"

#include <QAction>
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>

BinCQliteNewTableDialog::BinCQliteNewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinCQliteNewTableDialog)
{
    ui->setupUi(this);

    auto addAction = new QAction("Add field", this);
    auto deleteField = new QAction("Remove field", this);
    ui->tableWidget->addActions({ addAction, deleteField });

    auto dataTypes = [&](QWidget *parent) {
        auto listTypes = new QComboBox(parent);
        listTypes->addItems({"INTEGER", "DOUBLE", "TEXT", "DATE", "TIME", "BOOL"});

        return listTypes;
    };

    connect(addAction, &QAction::triggered, [&](){
        int nfilas = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nfilas);
        ui->tableWidget->setCellWidget(nfilas, 1, dataTypes(this));
        ui->tableWidget->setCellWidget(nfilas, 2, new QRadioButton(this));
        ui->tableWidget->setCellWidget(nfilas, 3, new QCheckBox(this));
        ui->tableWidget->setCellWidget(nfilas, 4, new QCheckBox(this));
    });

    connect(deleteField, &QAction::triggered, [&](){
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    });
}

BinCQliteNewTableDialog::~BinCQliteNewTableDialog()
{
    delete ui;
}

QString BinCQliteNewTableDialog::addFieldResult() const
{
    QString res = QString("CREATE TABLE IF NOT EXISTS %1 (").arg(ui->leTableName->text());
    int nfilas = ui->tableWidget->rowCount();
    for(int i = 0; i < nfilas; ++i) {
        auto fieldName = ui->tableWidget->item(i,0)->text();
        auto fieldType = static_cast<QComboBox *>(ui->tableWidget->cellWidget(i,1))->currentText();
        bool primaryKeyField = static_cast<QRadioButton *>(ui->tableWidget->cellWidget(i,2))->isChecked();
        bool notNullField = static_cast<QCheckBox *>(ui->tableWidget->cellWidget(i,3))->isChecked();
        bool autoincrementField = static_cast<QCheckBox *>(ui->tableWidget->cellWidget(i,4))->isChecked();

        res += fieldName + " " + fieldType;

        if(primaryKeyField) {
            res += " PRIMARY KEY";
        }
        if(autoincrementField) {
            res += " AUTOINCREMENT";
        }
        if(notNullField) {
            res += " NOT NULL";
        }
        res += ",";
    }
    res[res.size() - 1] = ')';
    return res;
}

void BinCQliteNewTableDialog::on_btnAccept_clicked()
{
    accept();
}


void BinCQliteNewTableDialog::on_btnCancel_clicked()
{
    reject();
}

