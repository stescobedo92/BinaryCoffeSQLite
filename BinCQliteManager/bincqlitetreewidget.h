#ifndef BINCQLITETREEWIDGET_H
#define BINCQLITETREEWIDGET_H

#include <QTreeWidget>
#include <QWidget>

class QAction;

class BinCQLiteTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    BinCQLiteTreeWidget(QWidget* parent=nullptr);
signals:
    void newTable();
private:
    QAction* mActionNewTable;
};

#endif // BINCQLITETREEWIDGET_H
