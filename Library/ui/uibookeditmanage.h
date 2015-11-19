#ifndef UIBOOKEDITMANAGE_H
#define UIBOOKEDITMANAGE_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class NewBookUI;

class UIBookEditManage : public QWidget
{
    Q_OBJECT

public:
    UIBookEditManage(QWidget *parent = 0);
    ~UIBookEditManage();

private:
    void initUI();
    void createConnections();

private:
    NewBookUI *newBookUI;
    QHBoxLayout *topLayout;
    QPushButton *confirnBtn;
    QPushButton *cancelBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private slots:
    void slotCancel();
    void slotSave();
};

#endif // UIBOOKEDITMANAGE_H
