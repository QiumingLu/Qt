#ifndef UIUSERTYPE_H
#define UIUSERTYPE_H

#include <QWidget>

class QPushButton;
class QTableWidget;
class QHBoxLayout;
class QVBoxLayout;
class UserType;
class UIUserType : public QWidget
{
public:
    UIUserType(QWidget *parent = 0);
    ~UIUserType();

    void initTable();

private:
    void initUI();
    void createConnections();

private:
    QTableWidget *userTypeTable;
    QPushButton *deleteBtn;
    QPushButton *addBtn;
    QPushButton *closeBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private:
    QList<UserType*> userTypeList;
};

#endif // UIUSERTYPE_H
