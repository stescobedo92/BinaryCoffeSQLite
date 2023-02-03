#include "bincqlitetreewidget.h"
#include <QAction>

BinCQLiteTreeWidget::BinCQLiteTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    mActionNewTable = new QAction(QIcon(":images/table"), "New Table", this);
    mActionDropTable = new QAction(QIcon(":images/errorLine"), "Drop Table", this);;
    mActionDropDataBase = new QAction(QIcon(":images/management"), "Drop Data Base", this);;
    mActionSelectScript = new QAction(QIcon(":images/copia"), "Select script", this);;

    addActions({ mActionNewTable,  mActionDropTable, mActionDropDataBase, mActionSelectScript });

    connect(mActionNewTable, &QAction::triggered, [&](){
        emit newTable();
    });
    connect(mActionDropTable, &QAction::triggered, [&](){
        emit dropTable();
    });
    connect(mActionDropDataBase, &QAction::triggered, [&](){
        emit dropDataBase();
    });
    connect(mActionSelectScript, &QAction::triggered, [&](){
        emit selectDataScript();
    });

}
