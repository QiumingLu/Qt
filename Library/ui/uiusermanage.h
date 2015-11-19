#ifndef UIUSERMANAGE_H
#define UIUSERMANAGE_H

#include <QMainWindow>

class QTreeWidgetItem;
class QLabel;
class QSplitter;
class QGridLayout;
class UIUserManageTree;
class UIUserInformationManage;
class UIUserEditManage;
class UIRegister;
class UIUserType;
class UIMemberLevel;
class UIUserManage : public QMainWindow
{
    Q_OBJECT

public:
    UIUserManage(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~UIUserManage();

private:
    void initUI();
    void createConnections();

private:
    QLabel *banner;
    QSplitter *mainSplitter;
    QGridLayout *mainLayout;
    QWidget *mainWidget;

    UIUserManageTree *leftTree;
    UIUserInformationManage *userInformationManage;
    UIUserEditManage *userEditManage;
    UIRegister *uiRegister;
    UIUserType *uiUserType;
    UIMemberLevel *uiMemberLevel;

public slots:
    void slotTreeItemClick(QTreeWidgetItem*,int);
    void slotRegister();
};

#endif // UIUSERMANAGE_H
