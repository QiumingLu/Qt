#ifndef UIMEMBERLEVEL_H
#define UIMEMBERLEVEL_H

#include <QWidget>

class QPushButton;
class QTableWidget;
class QHBoxLayout;
class QVBoxLayout;
class MemberLevel;
class AddMemberLevel;
class UIMemberLevel : public QWidget
{
    Q_OBJECT

public:
    UIMemberLevel(QWidget *parent = 0);
    ~UIMemberLevel();

    void initTable();

private:
    void initUI();
    void createConnections();

private:
    QTableWidget *memberLevelTable;
    QPushButton *deleteBtn;
    QPushButton *addBtn;
    QPushButton *closeBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private:
    QList<MemberLevel*> memberList;
    AddMemberLevel *addMemberLevel;

private slots:
    void slotAdd();
    void slotEdit();
    void slotDelete();
};

#endif // UIMEMBERLEVEL_H
