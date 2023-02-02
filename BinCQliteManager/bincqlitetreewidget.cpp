#include "bincqlitetreewidget.h"
#include <QAction>

BinCQLiteTreeWidget::BinCQLiteTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    mActionNewTable = new QAction(QIcon(""), "New Table", this);
    addActions({ mActionNewTable });

    connect(mActionNewTable, &QAction::triggered, [&](){
        emit newTable();
    });
}
