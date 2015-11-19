#include "uibookcategory.h"
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "core/systype.h"
#include "model/bookcategory.h"
#include "ui/addbookcategory.h"

UIBookCateGory::UIBookCateGory(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIBookCateGory::~UIBookCateGory()
{

}

void UIBookCateGory::initUI()
{
    this->bookCateGoryTable = new QTableWidget();
    this->deleteBtn = new QPushButton("删除");
    this->addBtn = new QPushButton("添加");
    this->closeBtn = new QPushButton("取消");
    this->btnLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->btnLayout->addStretch();
    this->btnLayout->addWidget(deleteBtn);
    this->btnLayout->addWidget(addBtn);
    this->btnLayout->addWidget(closeBtn);

    this->mainLayout->addWidget(bookCateGoryTable);
    this->mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);
}

void UIBookCateGory::createConnections()
{
    QObject::connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->addBtn, SIGNAL(clicked()), this, SLOT(slotAdd()));
}

void UIBookCateGory::initTable()
{
    this->bookCateGoryList = SYSTYPE->getAllBookCateGory();
    QStringList tableColumnName;
    tableColumnName.append("类型名");
    tableColumnName.append("备注");

    this->bookCateGoryTable->setColumnCount(tableColumnName.size());
    this->bookCateGoryTable->setRowCount(bookCateGoryList.size());
    this->bookCateGoryTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < bookCateGoryList.size(); ++i)
    {
        bookCateGoryTable->setItem(i, 0, new QTableWidgetItem(bookCateGoryList.at(i)->getCateGoryName()));
        bookCateGoryTable->setItem(i, 1, new QTableWidgetItem());
    }
}

void UIBookCateGory::slotAdd()
{
    this->addCateGory = new AddBookCateGory();
    this->addCateGory->show();
}
