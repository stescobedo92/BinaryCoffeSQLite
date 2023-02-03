#ifndef BINCQLITENEWTABLEDIALOG_H
#define BINCQLITENEWTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class BinCQliteNewTableDialog;
}

class BinCQliteNewTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BinCQliteNewTableDialog(QWidget *parent = nullptr);
    ~BinCQliteNewTableDialog();
    QString addFieldResult() const;
private slots:
    void on_btnAccept_clicked();
    void on_btnCancel_clicked();

private:
    Ui::BinCQliteNewTableDialog *ui;
};

#endif // BINCQLITENEWTABLEDIALOG_H
