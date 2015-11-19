#include "uiadmin.h"
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

UIAdmin::UIAdmin(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIAdmin::~UIAdmin()
{

}

void UIAdmin::initUI()
{
    this->mainTable = new QTableWidget();
    this->cancelBtn = new QPushButton("取消");
    this->saveBtn = new QPushButton("保存");
    this->btnLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->btnLayout->addWidget(this->cancelBtn);
    this->btnLayout->addStretch();
    this->btnLayout->addWidget(this->saveBtn);
    this->mainLayout->addWidget(this->mainTable);
    this->mainLayout->addLayout(this->btnLayout);
}

void UIAdmin::createConnections()
{
    QObject::connect(this->cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancel()));
    QObject::connect(this->saveBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
}

void UIAdmin::slotCancel()
{
    int ret = QMessageBox::information(this, tr("提醒"), "确定放弃保存修改的内容？", "确定", "取消");
    if (ret == 0)
        close();
    else
        return;
}

void UIAdmin::slotSave()
{

}
