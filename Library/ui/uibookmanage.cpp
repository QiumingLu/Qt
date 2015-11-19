#include "uibookmanage.h"
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QSplitter>
#include <QCloseEvent>
#include "ui/uibookmanagetree.h"
#include "ui/uibookinformationmanage.h"
#include "ui/uibookeditmanage.h"
#include "ui/uibookcategory.h"


UIBookManage::UIBookManage(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags)
{
    this->initUI();
    this->createConnections();
}

UIBookManage::~UIBookManage()
{

}

void UIBookManage::initUI()
{
    this->setWindowTitle(tr("图书管理模块"));
    this->setWindowState(Qt::WindowMaximized);

    this->banner = new QLabel();
    this->banner->setPixmap(QPixmap(":/006.jpg"));
    this->banner->setScaledContents(true);

    this->leftTree = new UIBookManageTree(this);
    this->bookInfomationManage = new UIBookInformationManage();
    this->bookEditManage = new UIBookEditManage();
    this->editBookManage = new UIBookInformationManage();
    this->uiBookCateGory = new UIBookCateGory();
    this->bookEditManage->hide();
    this->editBookManage->hide();
    this->uiBookCateGory->hide();

    this->mainSplitter = new QSplitter(Qt::Horizontal);
    this->mainSplitter->addWidget(this->leftTree);
    this->mainSplitter->addWidget(this->bookInfomationManage);
    this->mainSplitter->addWidget(this->bookEditManage);
    this->mainSplitter->addWidget(this->editBookManage);
    this->mainSplitter->addWidget(this->uiBookCateGory);
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

void UIBookManage::createConnections()
{
    QObject::connect(this->leftTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                     this, SLOT(slotTreeItemClick(QTreeWidgetItem*,int)));
}

void UIBookManage::slotTreeItemClick(QTreeWidgetItem *item, int)
{
    QString parentName;
    if (item->parent() != NULL)
    {
        parentName = item->parent()->text(0);

        if (parentName == "查看书籍的信息")
        {
            int bookType = item->data(0, Qt::UserRole).toInt();
            this->bookInfomationManage->initBookTable(bookType);
            this->bookInfomationManage->show();
            this->bookEditManage->hide();
            this->editBookManage->hide();
            this->uiBookCateGory->hide();
        }

        else if (parentName == "编辑书籍的信息")
        {
            if (item->text(0) == "添加新书")
            {
                this->bookEditManage->show();
                this->bookInfomationManage->hide();
                this->editBookManage->hide();
                this->uiBookCateGory->hide();
            }
            else if (item->text(0) == "编辑旧书")
            {
                this->editBookManage->initEditOldBook();
                this->editBookManage->show();
                this->bookEditManage->hide();
                this->bookInfomationManage->hide();
                this->uiBookCateGory->hide();
            }
        }
        else if (parentName == "书籍字典管理")
        {
            if (item->text(0) == "查看图书类别字典表")
            {
                this->uiBookCateGory->initTable();
                this->uiBookCateGory->show();
                this->bookEditManage->hide();
                this->editBookManage->hide();
                this->bookInfomationManage->hide();
            }
        }
    }
}
