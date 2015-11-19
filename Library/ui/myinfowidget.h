#ifndef MYINFOWIDGET_H
#define MYINFOWIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QCheckBox;
class QHBoxLayout;
class QPushButton;
class QGridLayout;
class QGroupBox;
class QScrollBar;
class Readers;

class MyInfoWidget : public QWidget
{
    Q_OBJECT

public:
    MyInfoWidget(QWidget *parent = 0);
    ~MyInfoWidget();

    void initInfomation(Readers *reader);

private:
    void initUI();
    void createConnections();

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
    QLineEdit *m_userBirthday;
    QLineEdit *m_userPhone;
    QLineEdit *m_userMobile;
    QLineEdit *m_userMail;
    QLineEdit *m_userCardName;
    QLineEdit *m_userCardId;
    QLineEdit *m_userLevel;
    QLineEdit *m_userRemark;

    QPushButton *m_ConfirmBtn;
    QPushButton *m_Cancel;

    QHBoxLayout *m_btnLayout;
    QGridLayout *userInfoLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;

    QWidget *gridWidget;
    QScrollBar *m_VScrollBar;
    QHBoxLayout *mainLayout;

    Readers *reader;

private slots:
    void slotClose();
    void slotSave();
    void displayListView(int);

};

#endif // MYINFOWIDGET_H
