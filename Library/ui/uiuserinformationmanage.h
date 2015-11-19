#ifndef UIUSERINFORMATIONMANAGE_H
#define UIUSERINFORMATIONMANAGE_H

#include <QWidget>

class QTableWidget;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class Managers;
class AddManagerBtn;
class EditManagerBtn;
class UIUserInformationManage : public QWidget
{
    Q_OBJECT

public:
    UIUserInformationManage(QWidget *parent = 0);
    ~UIUserInformationManage();

    void initManagerTable(int userType);

private:
    void initUI();
    void createConections();

private:
    QList<Managers*> managerVec;
    AddManagerBtn *addManager;
    EditManagerBtn *editManager;

private:
    QTableWidget *managerTable;
    QPushButton *deleteBtn;
    QPushButton *addBtn;
    QPushButton *closeBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private slots:
    void slotEdit();
    void slotDetail();
    void slotDelete();
    void slotAdd();
};

#endif // UIUSERINFORMATIONMANAGE_H
