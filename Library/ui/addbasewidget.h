#ifndef ADDBASEWIDGET_H
#define ADDBASEWIDGET_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;
class AddBaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddBaseWidget(QWidget *parent = 0);
    virtual ~AddBaseWidget();

protected:
    void initUI();
    void createConnections();
    virtual void initTable() = 0;
    virtual QVector<QString> getTableText() const = 0;

protected:
    QPushButton *cancelBtn;
    QPushButton *saveBtn;
    QTableWidget *mainTable;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

protected slots:
    virtual void slotSave() = 0;
    void slotCancel();
};
#endif // ADDBASEWIDGET_H
