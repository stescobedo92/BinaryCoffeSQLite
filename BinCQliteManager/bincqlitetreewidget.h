#ifndef BINCQLITETREEWIDGET_H
#define BINCQLITETREEWIDGET_H

#include <QTreeWidget>
#include <QWidget>

class QAction;

class BinCQLiteTreeWidget : public QTreeWidget
{
public:
    BinCQLiteTreeWidget(QWidget* parent=nullptr);
private:
    QAction* mActionNewTable;
};

#endif // BINCQLITETREEWIDGET_H
