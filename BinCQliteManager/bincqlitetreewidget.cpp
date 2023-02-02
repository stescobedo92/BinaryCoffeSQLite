#include "bincqlitetreewidget.h"
#include <QAction>

BinCQLiteTreeWidget::BinCQLiteTreeWidget(QWidget* parent) : QTreeWidget(parent)
{
    mActionNewTable = new QAction(QIcon(""), "New Table", this);
    mActionNewTable->setDisabled(true);
    addActions({ mActionNewTable });

    connect(mActionNewTable, &QAction::triggered, [&](){
        auto item = currentItem();
        if(item == nullptr) {
            return;
        }
        auto pather = item->parent();
        if( pather == nullptr) {
            emit newTable();
        }
    });
}
