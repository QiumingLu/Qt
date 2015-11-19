#ifndef UIREGISTER_H
#define UIREGISTER_H

#include <QDialog>
#include "ui/customdialog.h"

class QLabel;
class QCheckBox;
class QPushButton;
class QHBoxLayout;
class QGridLayout;
class QGroupBox;
class QLineEdit;
class QDateEdit;
class QComboBox;
class User;
class Readers;
class UIRegister : public CustomDialog
{
    Q_OBJECT

public:
    UIRegister(QWidget *parent = 0);
    ~UIRegister();
    void initLayout();
    void createConnection();
    void addNewReaderToSysType();

private:
    QLabel *m_Code;
    QLabel *m_Name;
    QLabel *m_PassWord;
    QLabel *m_RePassWord;
    QLabel *m_Sex;
    QLabel *m_Birthday;
    QLabel *m_Phone;
    QLabel *m_Mobile;
    QLabel *m_Mail;
    QLabel *m_CardName;
    QLabel *m_CardID;
    QLabel *m_Level;
    QLabel *m_Remark;

    QLineEdit *m_userCode;
    QLineEdit *m_userName;
    QLineEdit *m_userPsw;
    QLineEdit *m_userRePsw;
    QCheckBox *m_Male;
    QCheckBox *m_Female;
    QCheckBox *m_Other;
    QDateEdit *m_userBirthday;
    QLineEdit *m_userPhone;
    QLineEdit *m_userMobile;
    QLineEdit *m_userMail;
    QLineEdit *m_userCardName;
    QLineEdit *m_userCardId;
    QComboBox *m_userLevel;
    QLineEdit *m_userRemark;

    QLabel *m_CodeRequire;
    QLabel *m_NameRequire;
    QLabel *m_PswRequire;
    QLabel *m_SexRequire;
    QLabel *m_CardNameRequire;
    QLabel *m_CardIDRequire;
    QLabel *m_LevelRequire;

    QPushButton *m_ConfirmBtn;
    QPushButton *m_Cancel;

    QHBoxLayout *m_btnLayout;
    QGridLayout *registerLayout;
    QGroupBox *groupBox;
    QGridLayout *mainLayout;

    Readers *readers;
    User *user;

signals:
    void registerSuccess();

private slots:
    void slotOnRegister();
    void slotOnCheckBox();
};

#endif // UIREGISTER_H
