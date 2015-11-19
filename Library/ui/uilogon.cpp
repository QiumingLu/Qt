#include "uilogon.h"
#include <QFutureWatcher>
#include <QApplication>
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QAbstractButton>
#include <QtConcurrent/QtConcurrent>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <dao/basedao.h>
#include "ui/busywaitdialog.h"
#include "model/sysenviroment.h"
#include "model/user.h"
#include "uiregister.h"
#include "dao/daouser.h"
#include "dao/DaoHeader.h"
#include "core/systype.h"
#include "core/sysinfoio.h"
#include "ui/iconedlineedit.h"

UILogon::UILogon(QWidget *parent) :
    CustomDialog(parent)
{
    this->initUI();
    this->users = SysInfoIO::readfromfileforUser();
    this->ifInputName = false;
    this->ifInputPsw = false;
    this->createConnection();
}

UILogon::~UILogon()
{
    delete m_pName;
    delete m_pPassWord;
    delete m_userCode;
    delete m_userPassWord;
    delete m_rememberWord;
    delete m_login;
    delete m_register;
    delete m_cancel;
    delete logonGridLayout;
    delete logonGroupBox;
    delete copyright;
    delete mainLayout;
}

/*
 * @brief
 * 界面初始化
 * @name initUI()
 * @arg
 * void
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::initUI()
{
    this->setFixedSize(750, 500);
    this->setWindowTitle(tr("欢迎登陆图书管理系统"));
    this->m_pName = new QLabel(tr("用户名"));
    this->m_pPassWord = new QLabel(tr("密码"));
    this->m_userCode = new IconedLineEdit(this);
    this->m_userCode->setFixedHeight(26);
    this->m_userPassWord = new IconedLineEdit(this);
    this->m_userPassWord->setFixedHeight(26);

    this->m_userCode->setFocus();
    this->m_userCode->setIcon(QIcon(":/002.png"));
    this->m_userCode->setStyleSheet("color: gray;");
    this->m_userCode->setText("请输入用户名");

    this->m_userPassWord->setIcon(QIcon(":/001.png"));
    this->m_userPassWord->setStyleSheet("color: gray;");
    this->m_userPassWord->setText("请输入密码");

    this->m_rememberWord = new QCheckBox(tr("记住密码"));
    this->m_login = new QPushButton(tr("登陆"));
    this->m_login->setEnabled(false);
    this->m_register = new QPushButton(tr("注册"));
    this->m_cancel = new QPushButton(tr("取消"));

    this->logonGridLayout = new QGridLayout();
    this->logonGridLayout->setRowStretch(0, 1);
    this->logonGridLayout->setRowStretch(1, 1);
    this->logonGridLayout->setRowStretch(2, 1);
    this->logonGridLayout->addWidget(this->m_pName, 0, 4, 1, 2);
    this->logonGridLayout->addWidget(this->m_pPassWord, 1, 4, 1, 2);
    this->logonGridLayout->addWidget(this->m_userCode, 0, 6, 1, 14);
    this->logonGridLayout->addWidget(this->m_userPassWord, 1, 6, 1, 14);
    this->logonGridLayout->addWidget(this->m_rememberWord, 2, 0, 1, 8);
    this->logonGridLayout->addWidget(this->m_login, 2, 8, 1, 4);
    this->logonGridLayout->addWidget(this->m_register, 2, 12, 1, 4);
    this->logonGridLayout->addWidget(this->m_cancel, 2, 16, 1, 4);

    this->logonGroupBox = new QGroupBox();
    this->logonGroupBox->setLayout(this->logonGridLayout);
    this->logonGroupBox->setStyleSheet("background: white"/* rgb(0, 62, 79); color: rgb(136, 204, 216)"*/);

    this->copyright = new QLabel();
    this->copyright->setText(tr("COPYRIGHT @ 2014 Library"));

    this->mainLayout = new QGridLayout();
    this->mainLayout->setRowStretch(0, 4);
    this->mainLayout->setRowStretch(1, 3);
    this->mainLayout->setRowStretch(2, 3);
    this->mainLayout->setColumnStretch(0, 10);
    this->mainLayout->setColumnStretch(1, 6);
    this->mainLayout->setColumnStretch(2, 3);
    this->mainLayout->addWidget(this->logonGroupBox, 1, 1, 1, 1);
    this->mainLayout->addWidget(this->copyright, 3, 0, 1, 1);

    this->setLayout(this->mainLayout);
}


/*
 * @brief
 * 信号槽连接函数
 * @name createConnection()
 * @arg
 * void
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::createConnection()
{
    //登陆按钮
    QObject::connect(this->m_login, SIGNAL(clicked()), this, SLOT(slotOnLogon()));
    //用户输入框
    QObject::connect(this->m_userCode, SIGNAL(textChanged(QString)), this, SLOT(slotOnCheckUserRecord()));
    //记住密码
    QObject::connect(this->m_rememberWord, SIGNAL(clicked()), this, SLOT(slotOnRememberPsw()));
    //密码框输入限制
    QObject::connect(this->m_userPassWord, SIGNAL(textEdited(QString)), this, SLOT(slotPasswordEdit(QString)));

    QObject::connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(slotFocusChanged(QWidget*, QWidget*)));

    QObject::connect(this->m_register, SIGNAL(clicked()), this, SLOT(slotShowRegister()));

    QObject::connect(this->m_cancel, SIGNAL(clicked()), this, SLOT(slotCancelLogon()));
}

/*
 * @brief
 * 登陆系列操作
 * @name slotOnLogon()
 * @arg
 * void
 * @return bool
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool UILogon::slotOnLogon()
{
    User *user = new User();
    user->setUserCode(this->m_userCode->text());

    /*如果输入的是md5，则无需转换*/
   if (this->m_userPassWord->text().length() == 32) {
        user->setUserPsw(this->m_userPassWord->text());
    } else {
        QString md5password;
        QByteArray bb;
        bb = QCryptographicHash::hash(this->m_userPassWord->text().toLatin1(), QCryptographicHash::Md5);
        md5password.append(bb.toHex());
        user->setUserPsw(md5password);
    }

    /*更新用户最近的登陆时间*/
    user->setUserLastLogTime(QDateTime::currentDateTime());

    for (int i = 0; i < users.size(); ++i)
    {
        User *tmpuser = users.at(i);
        if (tmpuser->getUserCode() == this->m_userCode->text())
        {
            users.removeAt(i);
            SysInfoIO::writetofileforUser(users);
        }
    }

    /*打开数据库，验证用户登陆信息是否正确，正确，则登陆成功，错误，则登陆失败*/
    if (GLobal_DB->open())
    {
        QSqlQuery query(*GLobal_DB);
        query.prepare("select * from USER where USER_CODE =:code and USER_PSW =:psw");
        query.bindValue(":code", user->getUserCode());
        query.bindValue(":psw", user->getUserPsw());

        int flag = query.exec();
        if (flag) {
            if (!query.next()) {
                QMessageBox::warning(this, tr("错误"), tr("验证失败"), "确定");
            } else {
                int idx = query.record().indexOf("USER_ID");
                int user_id = query.value(idx).toInt();
                user->setUserID(user_id);

                idx = query.record().indexOf("USER_TYPE");
                int userType = query.value(idx).toInt();
                user->setUserType(userType);

                idx = query.record().indexOf("USER_NAME");
                QString userName = query.value(idx).toString();
                user->setUserName(userName);

                idx = query.record().indexOf("SEX");
                int userSex = query.value(idx).toInt();
                user->setSex(userSex);

                idx = query.record().indexOf("BIRTHDAY");
                QString birthday = query.value(idx).toString();
                user->setBirthDay(birthday);

                idx = query.record().indexOf("PHONE");
                QString phone = query.value(idx).toString();
                user->setPhone(phone);

                idx = query.record().indexOf("MOBILE");
                QString mobile = query.value(idx).toString();
                user->setMobile(mobile);

                idx = query.record().indexOf("MAIL");
                QString mail = query.value(idx).toString();
                user->setMail(mail);

                idx = query.record().indexOf("USER_REMARK");
                QString userRemark = query.value(idx).toString();
                user->setUserRemark(userRemark);

                SysEnviroment::getInstance()->setUser(user);

                GLobal_DB->close();

                if (this->m_rememberWord->isChecked())
                {
                    users.insert(0, user);
                    SysInfoIO::writetofileforUser(users);
                }

                //初始化单例类
                QFutureWatcher<void> futureWatcher;
                BusyWaitDialog busyDialog;
                busyDialog.setMessage(tr("加载中..."));
                QObject::connect(&futureWatcher, SIGNAL(finished()), &busyDialog, SLOT(close()));
                futureWatcher.setFuture(QtConcurrent::run(this, &UILogon::initSystypeData));
                busyDialog.exec();
                futureWatcher.waitForFinished();

                this->accept();
            }
        } else {
            QMessageBox::information(this, tr("提示"), tr("数据库故障，用户验证失败"), "确定");
            GLobal_DB->close();
        }
        return false;
    } else {
        QMessageBox::warning(this, tr("提示"), tr("连接设置错误"), "确定");
    }
    return false;
}

/*
 * @brief
 * 当用户输入用户名的时候，验证该用户之前是否已经选择了记住密码，
 * 如果选择，则自动填充密码，并且将登陆按钮改为true，记住密码变为选中。
 * @name slotOnCheckUserRecord()
 * @arg
 * void
 * @return bool
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
bool UILogon::slotOnCheckUserRecord()
{
    for (int i = 0; i < users.size(); ++i)
    {
        QString tmpstr = users.at(i)->getUserCode();
        if (this->m_userCode->text().compare(tmpstr) == 0)
        {
            User *tmpuser = users.at(i);
            this->m_userPassWord->setEchoMode(QLineEdit::Password);
            this->m_login->setEnabled(true);
            this->m_userPassWord->setText(tmpuser->getUserPsw());
            this->m_rememberWord->setChecked(true);
            return true;
        }
    }
    return false;
}

/*
 * @brief
 * 本函数实现“记住密码”响应操作，取消当前用户的“记住密码”时，立马清楚本地记录
 * @name slotOnRememberPsw()
 * @arg
 * void
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::slotOnRememberPsw()
{
    if (!this->m_rememberWord->isChecked())
    {
        for (int i = 0; i < users.size(); ++i)
        {
            if (users.at(i)->getUserCode().compare(this->m_userCode->text()) == 0)
            {
                users.removeAt(i);
                SysInfoIO::writetofileforUser(users);
            }
        }
    }
}



/*
 * @brief
 * 设置特定字符不能在密码框中输入
 * @name slotPasswordEdit(QString text)
 * @arg
 * QString text
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::slotPasswordEdit(QString text)
{
    QRegExp rx("\\s|\\t|\\'|\\`");
    if (rx.indexIn(text) != -1)
    {
        text.chop(1);
        QLineEdit *edit = qobject_cast<QLineEdit*>(sender());
        edit->setText(text);
    }
}

/*
 * @brief
 * 判断鼠标焦点是否发生改变
 * @name slotFocusChanged(QWidget *before, QWidget *after)
 * @arg
 * QWidget *before [In]改变前的widget状态
 * QWidget *after  [In]改变后的widget状态
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::slotFocusChanged(QWidget *before, QWidget *after)
{
    if (!ifInputName && after == this->m_userCode)
    {
        this->m_userCode->clear();
        this->m_userCode->setStyleSheet("color: black");
        this->ifInputName = true;
    }
    else if(!ifInputPsw && after == this->m_userPassWord)
    {
        this->m_userPassWord->clear();
        this->m_userPassWord->setStyleSheet("color: black");
        this->m_userPassWord->setEchoMode(QLineEdit::Password);     //切换输入模式
        this->ifInputPsw = true;
    }

    if (before == this->m_userCode && this->m_userCode->text() == "")
    {
        this->m_userCode->setStyleSheet("color: gray");
        this->m_userCode->setText("请输入用户名");
        this->ifInputName = false;
    }
    else if (before == this->m_userPassWord && this->m_userPassWord->text() == "")
    {
        this->m_userPassWord->setStyleSheet("color: gray");
        this->m_userPassWord->setText("请输入密码");
        this->ifInputPsw = false;
        this->m_userPassWord->setEchoMode(QLineEdit::Normal);
    }

    if (ifInputName && ifInputPsw)
    {
        this->m_login->setEnabled(true);
    }
}


/*
 * @brief
 * 响应注册按钮后出现注册界面
 * @name slotShowRegister()
 * @arg
 * void
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::slotShowRegister()
{
    UIRegister uiRegister;
    uiRegister.exec();
}

/*
 * @brief
 * 响应取消按钮后关闭程序
 * @name slotCancelLogon()
 * @arg
 * void
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::slotCancelLogon()
{
    exit(0);
}

/*
 * @brief
 * 更新用户登陆时间
 * @name slotCancelLogon()
 * @arg
 * void
 * @return void
 * @author
 * QiumingLu Email:12281116@bjtu.edu.cn
 * @test
 * no
 */
void UILogon::updateLastTime()
{
    User *user = SysEnviroment::getInstance()->getUser();
    DaoUser *pDaoUser = new DaoUser();
    QVector<User*> userList = pDaoUser->Select(user, COND_ID);
    foreach (User *m_user, userList) {
        QDateTime currentDate = SysEnviroment::getInstance()->getUser()->getUserLastLogTime();
        m_user->setUserLastLogTime(currentDate);
        pDaoUser->Update(m_user);
    }
    delete pDaoUser;
    pDaoUser = NULL;
}

void UILogon::initSystypeData()
{
    SYSTYPE->sysInit();
}
void UILogon::closeEvent(QCloseEvent *event)
{
    exit(0);
}
