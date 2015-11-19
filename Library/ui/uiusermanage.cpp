#include "uiusermanage.h"
#include <QLabel>
#include <QSplitter>
#include <QGridLayout>
#include "ui/uiusermanagetree.h"
#include "ui/uiuserinformationmanage.h"
#include "ui/uiusereditmanage.h"
#include "core/sysinclude.h"
#include "ui/uiregister.h"
#include "ui/uiusertype.h"
#include "ui/uimemberlevel.h"

UIUserManage::UIUserManage(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags)
{
    this->initUI();
    this->createConnections();
}

UIUserManage::~UIUserManage()
{

}

void UIUserManage::initUI()
{
    this->setWindowTitle("图书馆人员管理模块");
    this->setWindowState(Qt::WindowMaximized);

    this->banner = new QLabel();
    this->banner->setPixmap(QPixmap(":/006.jpg"));
    this->banner->setScaledContents(true);

    this->leftTree = new UIUserManageTree(this);
    this->userInformationManage = new UIUserInformationManage(this);
    this->userEditManage = new UIUserEditManage(this);
    this->uiUserType = new UIUserType(this);
    this->uiMemberLevel = new UIMemberLevel(this);
    this->userEditManage->hide();
    this->uiUserType->hide();
    this->uiMemberLevel->hide();

    this->mainSplitter = new QSplitter(Qt::Horizontal);
    this->mainSplitter->addWidget(this->leftTree);
    this->mainSplitter->addWidget(this->userInformationManage);
    this->mainSplitter->addWidget(this->userEditManage);
    this->mainSplitter->addWidget(this->uiUserType);
    this->mainSplitter->addWidget(this->uiMemberLevel);
    this->mainSplitter->setStretchFactor(1, 1);
    this->mainSplitter->setStretchFactor(2, 1);
    this->mainSplitter->setStretchFactor(3, 1);
    this->mainSplitter->setStretchFactor(4, 1);

    this->mainLayout = new QGridLayout();
    this->mainLayout->setRowStretch(0, 1);
    this->mainLayout->setRowStretch(1, 5);
    this->mainLayout->addWidget(this->banner, 0, 0, 1, 1);
    this->mainLayout->addWidget(this->mainSplitter, 1, 0, 9, 1);

    this->mainWidget = new QWidget();
    this->mainWidget->setLayout(this->mainLayout);
    this->setCentralWidget(this->mainWidget);
}

void UIUserManage::createConnections()
{
    QObject::connect(this->leftTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                     this, SLOT(slotTreeItemClick(QTreeWidgetItem*,int)));
}

void UIUserManage::slotTreeItemClick(QTreeWidgetItem *item, int)
{
    QString parentName;
    if (item->parent() != NULL)
    {
        parentName = item->parent()->text(0);
        if (parentName == "查看人员信息")
        {
            int userType = item->data(0, Qt::UserRole).toInt();

            if (userType != sysinclude::reader)
            {
                this->userInformationManage->initManagerTable(userType);
                this->userInformationManage->show();
                this->userEditManage->hide();
                this->uiUserType->hide();
                this->uiMemberLevel->hide();
            }

            else if (userType == sysinclude::reader)
            {
                this->userEditManage->show();
                this->userEditManage->initReaderTable();
                this->userInformationManage->hide();
                this->uiUserType->hide();
                this->uiMemberLevel->hide();
            }
        }
        else if (parentName == "编辑人员信息")
        {
            if(item->text(0) == "添加新用户")
            {
                this->uiRegister = new UIRegister();
                uiRegister->show();
                QObject::connect(this->uiRegister, SIGNAL(registerSuccess()), this, SLOT(slotRegister()));
            }
            else if (item->text(0) == "编辑旧的人员")
            {
                this->userInformationManage->hide();
                this->userEditManage->hide();
                this->uiUserType->hide();
                this->uiMemberLevel->hide();
            }
        }

        else if (parentName == "人员字典管理")
        {
            if (item->text(0) == "人员类别字典表")
            {
                this->uiUserType->initTable();
                this->uiUserType->show();
                this->userInformationManage->hide();
                this->userEditManage->hide();
                this->uiMemberLevel->hide();
            }
            else if (item->text(0) == "会员等级字典表")
            {
                this->uiMemberLevel->initTable();
                this->uiMemberLevel->show();
                this->userEditManage->hide();
                this->userInformationManage->hide();
                this->uiUserType->hide();
            }
        }
    }
}

void UIUserManage::slotRegister()
{
    this->uiRegister->addNewReaderToSysType();
}
