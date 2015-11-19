#ifndef ADDMEMBERLEVEL_H
#define ADDMEMBERLEVEL_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;
class MemberLevel;
class AddMemberLevel : public QWidget
{
    Q_OBJECT

public:
    AddMemberLevel(QWidget *parent = 0);
    ~AddMemberLevel();

    bool initLevelInfo(MemberLevel *memberLevel);

private:
    void initUI();
    void createConnections();
    void initTable();
    QVector<QString> getMemberLevelVec() const;

    MemberLevel *memberLevel;

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

#endif // ADDMEMBERLEVEL_H
