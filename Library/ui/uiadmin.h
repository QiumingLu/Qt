#ifndef UIADMIN_H
#define UIADMIN_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;
class UIAdmin : public QWidget
{
    Q_OBJECT

public:
    UIAdmin(QWidget *parent = 0);
    ~UIAdmin();

private:
    void initUI();
    void createConnections();

private:
    QPushButton *cancelBtn;
    QPushButton *saveBtn;
    QTableWidget *mainTable;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private slots:
    void slotSave();
    void slotCancel();
};

#endif // UIADMIN_H
