#include "addbasewidget.h"
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "core/sysinclude.h"

AddBaseWidget::AddBaseWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

AddBaseWidget::~AddBaseWidget()
{
    SAFE_DELETE(mainTable);
    SAFE_DELETE(cancelBtn);
    SAFE_DELETE(saveBtn);
    SAFE_DELETE(btnLayout);
    SAFE_DELETE(mainLayout);
}

void AddBaseWidget::initUI()
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
    this->setLayout(mainLayout);
}

void AddBaseWidget::createConnections()
{
    QObject::connect(this->cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancel()));
    QObject::connect(this->saveBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
}

void AddBaseWidget::slotCancel()
{
    int ret = QMessageBox::information(this, tr("提醒"), "确定放弃保存修改的内容？", "确定", "取消");
    if (ret == 0)
        close();
    else
        return;
}

