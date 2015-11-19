#include "myinfowidget.h"
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollBar>
#include <QMessageBox>
#include "model/sysenviroment.h"
#include "model/user.h"
#include "core/systype.h"
#include "core/sysinclude.h"
#include "model/readers.h"
#include "dao/daoreaders.h"
#include "dao/daouser.h"

MyInfoWidget::MyInfoWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

MyInfoWidget::~MyInfoWidget()
{

}

void MyInfoWidget::initUI()
{
    this->setFixedWidth(300);
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
    this->m_userPsw->setDisabled(true);
    this->m_userRePsw->setDisabled(true);
    this->m_userPsw->setEchoMode(QLineEdit::Password);
    this->m_userRePsw->setEchoMode(QLineEdit::Password);
    this->m_Male = new QCheckBox(tr("男"));
    this->m_Female = new QCheckBox(tr("女"));
    this->m_Other = new QCheckBox(tr("保密"));
    this->m_userBirthday = new QLineEdit();
    this->m_userPhone = new QLineEdit();
    this->m_userMobile = new QLineEdit();
    this->m_userMail = new QLineEdit();
    this->m_userCardName = new QLineEdit();
    this->m_userCardId = new QLineEdit();
    this->m_userLevel = new QLineEdit();
    this->m_userRemark = new QLineEdit();

    this->m_ConfirmBtn = new QPushButton(tr("保存"));
    this->m_Cancel = new QPushButton(tr("取消"));

    this->m_btnLayout = new QHBoxLayout();
    this->m_btnLayout->addWidget(m_ConfirmBtn);
    this->m_btnLayout->addStretch();
    this->m_btnLayout->addWidget(m_Cancel);

    this->userInfoLayout = new QGridLayout();
    this->userInfoLayout->addWidget(m_Code, 0, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Name, 1, 0, 1, 5);
    this->userInfoLayout->addWidget(m_PassWord, 2, 0, 1, 5);
    this->userInfoLayout->addWidget(m_RePassWord, 3, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Sex, 4, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Birthday, 5, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Phone, 6, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Mobile, 7, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Mail, 8, 0, 1, 5);
    this->userInfoLayout->addWidget(m_CardName, 9, 0, 1, 5);
    this->userInfoLayout->addWidget(m_CardID, 10, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Level, 11, 0, 1, 5);
    this->userInfoLayout->addWidget(m_Remark, 12, 0, 1, 5);

    this->userInfoLayout->addWidget(m_userCode, 0, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userName, 1, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userPsw, 2, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userRePsw, 3, 5, 1, 12);
    this->userInfoLayout->addWidget(m_Male, 4, 5, 1, 3);
    this->userInfoLayout->addWidget(m_Female, 4, 8, 1, 3);
    this->userInfoLayout->addWidget(m_Other, 4, 11, 1, 3);
    this->userInfoLayout->addWidget(m_userBirthday, 5, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userPhone, 6, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userMobile, 7, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userMail, 8, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userCardName, 9, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userCardId, 10, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userLevel, 11, 5, 1, 12);
    this->userInfoLayout->addWidget(m_userRemark, 12, 5, 1, 12);
    this->userInfoLayout->addLayout(m_btnLayout, 13, 0, 1, 17);

    this->groupBox = new QGroupBox(this);
    this->groupBox->setLayout(userInfoLayout);
    this->groupBox->setStyleSheet("backgroud: white");

    this->gridLayout = new QGridLayout(this);
    this->gridLayout->addWidget(groupBox);

    this->gridWidget = new QWidget(this);
    this->gridWidget->setLayout(gridLayout);

    this->m_VScrollBar = new QScrollBar(Qt::Vertical, this);

    this->mainLayout = new QHBoxLayout(this);
    this->mainLayout->addWidget(this->gridWidget);
    this->mainLayout->addWidget(this->m_VScrollBar);
    this->mainLayout->setMargin(2);
    this->mainLayout->setSpacing(0);

    this->setLayout(mainLayout);
}

void MyInfoWidget::initInfomation(Readers *reader)
{
    if (reader != NULL) {
        this->reader = reader;
        this->m_userCode->setText(reader->getUserCode());
        this->m_userName->setText(reader->getUserName());
        if (reader->getSex() == sysinclude::male) {
            this->m_Male->setChecked(true);
        } else if (reader->getSex() == sysinclude::female) {
            this->m_Female->setChecked(true);
        } else {
            this->m_Other->setChecked(true);
        }

        this->m_userBirthday->setText(reader->getBirthDay());
        this->m_userPhone->setText(reader->getPhone());
        this->m_userMobile->setText(reader->getMobile());
        this->m_userMail->setText(reader->getMail());
        this->m_userCardName->setText(reader->getCardName());
        this->m_userCardId->setText(reader->getCardId());
        this->m_userLevel->setText(QString::number(reader->getCardLevel()));
        this->m_userRemark->setText(reader->getUserRemark());
    }
}

void MyInfoWidget::createConnections()
{
    QObject::connect(this->m_Cancel, SIGNAL(clicked()), this, SLOT(slotClose()));
    QObject::connect(this->m_ConfirmBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
    QObject::connect(this->m_VScrollBar, SIGNAL(valueChanged(int)),
                     this, SLOT(displayListView(int)));
}

void MyInfoWidget::displayListView(int len)
{
    this->gridWidget->move(0, -len);
}

void MyInfoWidget::slotSave()
{
    this->reader->setUserCode(this->m_userCode->text());
    this->reader->setUserName(this->m_userName->text());
    if (this->m_Male->isChecked())
    {
        this->reader->setSex(sysinclude::male);
    } else if (this->m_Female->isChecked()) {
        this->reader->setSex(sysinclude::female);
    } else {
        this->reader->setSex(sysinclude::other);
    }
    this->reader->setBirthDay(this->m_userBirthday->text());
    this->reader->setPhone(this->m_userPhone->text());
    this->reader->setMobile(this->m_userMobile->text());
    this->reader->setMail(this->m_userMail->text());
    this->reader->setCardName(this->m_userCardName->text());
    this->reader->setCardId(this->m_userCardId->text());
    this->reader->setCardLevel(this->m_userLevel->text().toInt());
    this->reader->setUserRemark(this->m_userRemark->text());
    User *user = this->reader;
    DaoUser daouser;
    DaoReaders daoReaders;
    bool retUser = daouser.Update(user);
    if (retUser == false)
    {
        if (SysEnviroment::getInstance()->getUser()->getUserType() == sysinclude::reader)
        {
            user = SysEnviroment::getInstance()->getUser();
        } else {
            user = SYSTYPE->getUser(user->getUserID());
        }
        daouser.Update(user);
        QMessageBox::information(this, tr("information"), tr("保存失败！"), "确定");
        return ;
    }
    bool retReader = daoReaders.Update(reader);
    if (retUser && retReader)
    {
        QMessageBox::information(this, tr("information"), tr("保存成功！"), "确定");
        if (SysEnviroment::getInstance()->getUser()->getUserType() == sysinclude::reader)
        {
            SysEnviroment::getInstance()->setUser(user);
        }
        else
        {
            this->reader = SYSTYPE->reverReader(reader->getReaderId());
            user = SYSTYPE->reverUser(reader->getReaderId());
        }
    } else {
        QMessageBox::information(this, tr("information"), tr("保存失败！"), "确定");
    }
}

void MyInfoWidget::slotClose()
{
    this->close();
}
