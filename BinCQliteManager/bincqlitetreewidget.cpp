#include "bincqlitetreewidget.h"
#include <QAction>

BinCQLiteTreeWidget::BinCQLiteTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    mActionNewTable = new QAction(QIcon(""), "New Table", this);
    mActionDropTable = new QAction(QIcon(""), "Drop Table", this);;
    mActionDropDataBase = new QAction(QIcon(""), "Drop Data Base", this);;
    mActionSelectScript = new QAction(QIcon(""), "Select data", this);;

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
