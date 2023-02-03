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
    void dropTable();
    void dropDataBase();
    void selectDataScript();
private:
    QAction *mActionNewTable;
    QAction *mActionDropTable;
    QAction *mActionDropDataBase;
    QAction *mActionSelectScript;
};

#endif // BINCQLITETREEWIDGET_H
