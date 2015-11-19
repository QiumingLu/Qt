#include "uiregister.h"
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QCryptographicHash>
#include <QRegExp>
#include <QMessageBox>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include "model/user.h"
#include "model/readers.h"
#include "dao/daouser.h"
#include "dao/daoreaders.h"
#include "dao/basedao.h"
#include "core/sysinclude.h"
#include "dao/DaoHeader.h"
#include "core/systype.h"
#include "model/memberlevel.h"
#include "dao/daomemberlevel.h"


UIRegister::UIRegister(QWidget *parent) :
    CustomDialog(parent)
{
    this->initLayout();
    this->createConnection();
}

UIRegister::~UIRegister()
{

}

void UIRegister::initLayout()
{
    this->setFixedSize(750, 500);
    this->m_Code = new QLabel(tr("Library ID："));
    this->m_Name = new QLabel(tr("用户姓名："));
    this->m_PassWord = new QLabel(tr("密码："));
    this->m_RePassWord = new QLabel(tr("再输一次："));
    this->m_Sex = new QLabel(tr("性别："));
    this->m_Birthday = new QLabel(tr("出生日期："));
    this->m_Phone = new QLabel(tr("电话："));
    this->m_Mobile = new QLabel(tr("手机："));
    this->m_Mail = new QLabel(tr("邮箱："));
    this->m_CardName = new QLabel(tr("证件名称："));
    this->m_CardID = new QLabel(tr("证件编号："));
    this->m_Level = new QLabel(tr("会员级别："));
    this->m_Remark = new QLabel(tr("备注："));

    this->m_userCode = new QLineEdit();
    this->m_userName = new QLineEdit();
    this->m_userPsw = new QLineEdit();
    this->m_userRePsw = new QLineEdit();
    this->m_userPsw->setEchoMode(QLineEdit::Password);
    this->m_userRePsw->setEchoMode(QLineEdit::Password);
    this->m_Male = new QCheckBox(tr("男"));
    this->m_Female = new QCheckBox(tr("女"));
    this->m_Other = new QCheckBox(tr("保密"));
    this->m_userBirthday = new QDateEdit();
    this->m_userPhone = new QLineEdit();
    this->m_userMobile = new QLineEdit();
    this->m_userMail = new QLineEdit();
    this->m_userCardName = new QLineEdit();
    this->m_userCardId = new QLineEdit();
    this->m_userLevel = new QComboBox();
    this->m_userRemark = new QLineEdit();

    QList<MemberLevel*> memberLevelList = SYSTYPE->getAllMemberLevel();
    if (memberLevelList.size() == 0)
    {
        DaoMemberLevel daoMemberLevel;
        MemberLevel memberLevel;
        QVector<MemberLevel*> memberLevelVec = daoMemberLevel.Select(&memberLevel, COND_NULL);
        memberLevelList = memberLevelVec.toList();
    }

    for (int i = 0; i < memberLevelList.size(); ++i)
    {
        m_userLevel->addItem(memberLevelList.at(i)->getLevelName(),
                             memberLevelList.at(i)->getLevelId());
    }

    this->m_CodeRequire = new QLabel(tr("(*必填， 要求：字母、数字、下划线组成（4~30位），注册后不能再改变)"));
    this->m_NameRequire = new QLabel(tr("(*必填)"));
    this->m_PswRequire = new QLabel(tr("(*必填，要求：非汉字（4~30位)"));
    this->m_SexRequire = new QLabel(tr("(*必选)"));
    this->m_CardNameRequire = new QLabel(tr("(*必填)"));
    this->m_CardIDRequire = new QLabel(tr("(*必填)"));
    this->m_LevelRequire = new QLabel(tr("(*必填)"));

    this->m_ConfirmBtn = new QPushButton(tr("确定"));
    this->m_Cancel = new QPushButton(tr("取消"));

    this->m_btnLayout = new QHBoxLayout();
    this->m_btnLayout->addWidget(m_ConfirmBtn);
    this->m_btnLayout->addWidget(m_Cancel);
    this->m_btnLayout->addStretch();

    this->registerLayout = new QGridLayout();
    this->registerLayout->addWidget(m_Code, 0, 0, 1, 5);
    this->registerLayout->addWidget(m_Name, 1, 0, 1, 5);
    this->registerLayout->addWidget(m_PassWord, 2, 0, 1, 5);
    this->registerLayout->addWidget(m_RePassWord, 3, 0, 1, 5);
    this->registerLayout->addWidget(m_Sex, 4, 0, 1, 5);
    this->registerLayout->addWidget(m_Birthday, 5, 0, 1, 5);
    this->registerLayout->addWidget(m_Phone, 6, 0, 1, 5);
    this->registerLayout->addWidget(m_Mobile, 7, 0, 1, 5);
    this->registerLayout->addWidget(m_Mail, 8, 0, 1, 5);
    this->registerLayout->addWidget(m_CardName, 9, 0, 1, 5);
    this->registerLayout->addWidget(m_CardID, 10, 0, 1, 5);
    this->registerLayout->addWidget(m_Level, 11, 0, 1, 5);
    this->registerLayout->addWidget(m_Remark, 12, 0, 1, 5);

    this->registerLayout->addWidget(m_userCode, 0, 5, 1, 12);
    this->registerLayout->addWidget(m_userName, 1, 5, 1, 12);
    this->registerLayout->addWidget(m_userPsw, 2, 5, 1, 12);
    this->registerLayout->addWidget(m_userRePsw, 3, 5, 1, 12);
    this->registerLayout->addWidget(m_Male, 4, 5, 1, 3);
    this->registerLayout->addWidget(m_Female, 4, 8, 1, 3);
    this->registerLayout->addWidget(m_Other, 4, 11, 1, 3);
    this->registerLayout->addWidget(m_userBirthday, 5, 5, 1, 12);
    this->registerLayout->addWidget(m_userPhone, 6, 5, 1, 12);
    this->registerLayout->addWidget(m_userMobile, 7, 5, 1, 12);
    this->registerLayout->addWidget(m_userMail, 8, 5, 1, 12);
    this->registerLayout->addWidget(m_userCardName, 9, 5, 1, 12);
    this->registerLayout->addWidget(m_userCardId, 10, 5, 1, 12);
    this->registerLayout->addWidget(m_userLevel, 11, 5, 1, 12);
    this->registerLayout->addWidget(m_userRemark, 12, 5, 1, 12);
    this->registerLayout->addLayout(m_btnLayout, 13, 24, 1, 6);

    this->registerLayout->addWidget(m_CodeRequire, 0, 18, 1, 12);
    this->registerLayout->addWidget(m_NameRequire, 1, 18, 1, 8);
    this->registerLayout->addWidget(m_PswRequire, 2, 18, 1, 8);
    this->registerLayout->addWidget(m_SexRequire, 4, 18, 1, 8);
    this->registerLayout->addWidget(m_CardNameRequire, 9, 18, 1, 8);
    this->registerLayout->addWidget(m_CardIDRequire, 10, 18, 1, 8);
    this->registerLayout->addWidget(m_LevelRequire, 11, 18, 1, 8);

    this->groupBox = new QGroupBox();
    this->groupBox->setLayout(registerLayout);
    this->groupBox->setStyleSheet("backgroud: white");

    this->mainLayout = new QGridLayout();
    this->mainLayout->addWidget(groupBox);
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(mainLayout);
}

void UIRegister::createConnection()
{
    QObject::connect(this->m_ConfirmBtn, SIGNAL(clicked()), this, SLOT(slotOnRegister()));
    QObject::connect(this->m_Cancel, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->m_Male, SIGNAL(clicked()), this, SLOT(slotOnCheckBox()));
    QObject::connect(this->m_Female, SIGNAL(clicked()), this, SLOT(slotOnCheckBox()));
    QObject::connect(this->m_Other, SIGNAL(clicked()), this, SLOT(slotOnCheckBox()));
}

void UIRegister::slotOnCheckBox()
{
    if (sender() == m_Male)
    {
        m_Male->setCheckState(Qt::Checked);
        m_Female->setCheckState(Qt::Unchecked);
        m_Other->setCheckState(Qt::Unchecked);
    }
    else if (sender() == m_Female)
    {
        m_Female->setCheckState(Qt::Checked);
        m_Male->setCheckState(Qt::Unchecked);
        m_Other->setCheckState(Qt::Unchecked);
    }
    else if (sender() == m_Other)
    {
        m_Other->setCheckState(Qt::Checked);
        m_Male->setCheckState(Qt::Unchecked);
        m_Female->setCheckState(Qt::Unchecked);
    }
}

void UIRegister::slotOnRegister()
{
    this->readers = new Readers();
    QRegExp user_reg_exp("[A-Za-z0-9_]{4,30}");
    QRegExpValidator *user_validator = new QRegExpValidator(user_reg_exp);
    QString userCode = this->m_userCode->text();
    if (!user_validator->regExp().exactMatch(userCode))
    {
        QMessageBox::warning(this, tr("warning"), tr("Library ID 输入不正确"),"确定");
        this->m_userCode->setFocus();
        return;
    }
    this->readers->setUserCode(userCode);

    if (this->m_userName->text() == "")
    {
        QMessageBox::warning(this, tr("warning"), tr("用户姓名不能为空"), "确定");
        this->m_userName->setFocus();
        return;
    }
    this->readers->setUserName(this->m_userName->text());

    QRegExp password_reg_exp("[^\u4E00-\u9FA5]{4,30}");
    QRegExpValidator *password_validator = new QRegExpValidator(password_reg_exp);
    QString userPsw = this->m_userPsw->text();
    if (!password_validator->regExp().exactMatch(userPsw))
    {
        QMessageBox::warning(this, tr("warning"), tr("密码输入不正确"), "确定");
        this->m_userPsw->setFocus();
        return;
    }
    if ( userPsw != (this->m_userRePsw->text()) )
    {
        QMessageBox::warning(this, tr("warning"), tr("两次的密码输入不相同"), "确定");
        this->m_userRePsw->setFocus();
        return;
    }

    /*如果输入的是md5，则无需要转换*/
    if (userPsw.length() == 32) {
        this->readers->setUserPsw(userPsw);
    } else {
        QString md5password;
        QByteArray bb;
        bb = QCryptographicHash::hash(userPsw.toLatin1(),
                                      QCryptographicHash::Md5);
        md5password.append(bb.toHex());
        this->readers->setUserPsw(md5password);
    }

    if (this->m_Male->isChecked() || this->m_Female->isChecked() || this->m_Other->isChecked()) {
        if (this->m_Male->isChecked()) {
            this->readers->setSex(sysinclude::male);
        }
        else if (this->m_Female->isChecked()) {
            this->readers->setSex(sysinclude::female);
        }
        else {
            this->readers->setSex(sysinclude::other);
        }
    } else {
        QMessageBox::warning(this, tr("warning"), tr("请选择性别"), "确定");
        this->m_Male->setFocus();
        return ;
    }

    this->readers->setBirthDay(this->m_userBirthday->text());
    this->readers->setPhone(this->m_userPhone->text());
    this->readers->setMobile(this->m_userMobile->text());
    this->readers->setMail(this->m_userMail->text());
    this->readers->setUserType(sysinclude::reader);
    this->readers->setUserRemark(this->m_userRemark->text());

    if (this->m_userCardName->text() == "")
    {
        QMessageBox::warning(this, tr("waring"), tr("请输入证件名称"), "确定");
        this->m_userCardName->setFocus();
        return ;
    }

    if (this->m_userCardId->text() == "")
    {
        QMessageBox::warning(this, tr("waring"), tr("请输入证件号"), "确定");
        this->m_userCardId->setFocus();
        return ;
    }

    this->readers->setCardName(this->m_userCardName->text());
    this->readers->setCardId(this->m_userCardId->text());
    int levelId = this->m_userLevel->itemData(this->m_userLevel->currentIndex(),
                                              Qt::UserRole).toInt();
    this->readers->setCardLevel(levelId);
    QDate day = QDate::currentDate();
    this->readers->setDay(day);
    QDateTime currentTime = QDateTime::currentDateTime();
    this->readers->setUserCreateTime(currentTime);

    if (QSqlDatabase::database().driver()->Transactions)
    {
        if (QSqlDatabase::database().transaction())
        {
            DaoUser daouser;
            DaoReaders daoreaders;
            BaseDao baseDao;

            this->user = this->readers;
            bool user_flag = daouser.Add(user);

            QString userTableName = "USER";
            QString outField = "USER_ID";
            int userId = baseDao.getId(userTableName, outField);
            readers->setReaderId(userId);

            bool readers_flag = daoreaders.Add(readers);

            QString tableName = "READERS";
            QString outFields = "ID";
            int id = baseDao.getId(tableName, outFields);
            this->readers->setId(id);

            if (user_flag && readers_flag)
            {

                QSqlDatabase::database().rollback();
                QMessageBox::warning(this, tr("提醒"), tr("保存失败"), "确定");
            }

            if (QSqlDatabase::database().commit())
            {
                QMessageBox::information(this, tr("提醒"), tr("保存成功"), "确定");
                emit registerSuccess();
            }
            else
            {
                QMessageBox::warning(this, tr("提醒"), tr("保存失败"), "确定");
            }
        }
    }
}

void UIRegister::addNewReaderToSysType()
{
    SYSTYPE->addUser(this->user->getUserID(), this->user);
    SYSTYPE->addReader(this->readers->getReaderId(), this->readers);
}
