#include "uiusertype.h"
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "model/usertype.h"
#include "core/systype.h"

UIUserType::UIUserType(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIUserType::~UIUserType()
{

}

void UIUserType::initUI()
{
    this->userTypeTable = new QTableWidget();
    this->deleteBtn = new QPushButton("删除");
    this->addBtn = new QPushButton("添加");
    this->closeBtn = new QPushButton("取消");
    this->btnLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->btnLayout->addStretch();
    this->btnLayout->addWidget(deleteBtn);
    this->btnLayout->addWidget(addBtn);
    this->btnLayout->addWidget(closeBtn);

    this->mainLayout->addWidget(userTypeTable);
    this->mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);
}

void UIUserType::initTable()
{
    this->userTypeList = SYSTYPE->getAllUserType();
    QStringList tableColumnName;
    tableColumnName.append("人员类型");
    tableColumnName.append("备注");

    this->userTypeTable->setColumnCount(tableColumnName.size());
    this->userTypeTable->setRowCount(userTypeList.size());
    this->userTypeTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < userTypeList.size(); ++i)
    {
        this->userTypeTable->setItem(i, 0, new QTableWidgetItem(userTypeList.at(i)->getUserTypeName()));
    }
}

void UIUserType::createConnections()
{
    QObject::connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}
