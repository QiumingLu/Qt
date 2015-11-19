#ifndef UILOGON_H
#define UILOGON_H

#include <QDialog>
#include "ui/customdialog.h"

class QLabel;
class QCheckBox;
class QPushButton;
class QGridLayout;
class QGroupBox;
class User;
class IconedLineEdit;
class SysInfoIO;
class UILogon : public CustomDialog
{
    Q_OBJECT

public:
    explicit UILogon(QWidget *parent = 0);
    ~UILogon();
    static void updateLastTime();
    void closeEvent(QCloseEvent *event);

private:
    void initUI();
    void createConnection();
    void initSystypeData();

private:
    QLabel *m_pName;
    QLabel *m_pPassWord;
    IconedLineEdit *m_userCode;
    IconedLineEdit *m_userPassWord;
    QCheckBox *m_rememberWord;
    QPushButton *m_login;
    QPushButton *m_register;
    QPushButton *m_cancel;

    QGridLayout *logonGridLayout;
    QGroupBox *logonGroupBox;
    QLabel *copyright;
    QGridLayout *mainLayout;

    bool ifInputName;          //标记用户名输入框是否正在接受用户名
    bool ifInputPsw;           //标记密码输入框是否正在接受密码

    QList<User*> users;

private slots:
    bool slotOnLogon();
    bool slotOnCheckUserRecord();
    void slotOnRememberPsw();
    void slotPasswordEdit(QString text);
    void slotFocusChanged(QWidget*, QWidget*);
    void slotShowRegister();
    void slotCancelLogon();
};

#endif // UILOGON_H
