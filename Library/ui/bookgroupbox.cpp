#include "bookgroupbox.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QDateEdit>
#include "core/sysinclude.h"
#include "ui/uilendbook.h"

BookGroupBox::BookGroupBox(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

BookGroupBox::~BookGroupBox()
{
    SAFE_DELETE(m_bookName);
    SAFE_DELETE(m_bookCode);
    SAFE_DELETE(m_author);
    SAFE_DELETE(m_publishing);
    SAFE_DELETE(m_category);
    SAFE_DELETE(m_price);
    SAFE_DELETE(m_dateIn);
    SAFE_DELETE(m_quantity_In);
    SAFE_DELETE(m_quantity_Out);
    SAFE_DELETE(m_quantity);
    SAFE_DELETE(m_isBorrow);
    SAFE_DELETE(bookName);
    SAFE_DELETE(bookCode);
    SAFE_DELETE(author);
    SAFE_DELETE(publishing);
    SAFE_DELETE(category);
    SAFE_DELETE(price);
    SAFE_DELETE(dateIn);
    SAFE_DELETE(quantity_In);
    SAFE_DELETE(quantity_Out);
    SAFE_DELETE(quantity);
    SAFE_DELETE(isBorrow);
    SAFE_DELETE(m_lookDetail);
    SAFE_DELETE(lendBook);
    SAFE_DELETE(m_lendBook);
    SAFE_DELETE(bookLayout);
    SAFE_DELETE(bookBox);
}

void BookGroupBox::initUI()
{
    this->lendBook = new UILendBook();

    this->bookLayout = new QGridLayout(this);
    this->bookBox = new QGroupBox(this);

    this->m_bookName = new QLabel("书名：", this);
    this->m_bookCode = new QLabel("图书编号：", this);
    this->m_author = new QLabel("作者：", this);
    this->m_publishing = new QLabel("出版社：", this);
    this->m_category = new QLabel("类别：", this);
    this->m_price = new QLabel("定价：", this);
    this->m_dateIn = new QLabel("入馆时间：", this);
    this->m_quantity_In = new QLabel("在馆数目：", this);
    this->m_quantity_Out = new QLabel("已借出数目：", this);
    this->m_quantity = new QLabel("馆藏数目：", this);
    this->m_isBorrow = new QLabel("是否在馆内", this);

    this->bookName = new QLabel(this);
    this->bookCode = new QLabel(this);
    this->author = new QLabel(this);
    this->publishing = new QLabel(this);
    this->category = new QLabel(this);
    this->price = new QLabel(this);
    this->dateIn = new QLabel(this);
    this->quantity_In = new QLabel(this);
    this->quantity_Out = new QLabel(this);
    this->quantity = new QLabel(this);
    this->isBorrow = new QLabel(this);

    this->m_lookDetail = new QPushButton(tr("查看详细信息"));
    this->m_lendBook = new QPushButton(tr("借书"));

    this->bookLayout->addWidget(this->m_bookName, 0, 0, 1, 4);
    this->bookLayout->addWidget(this->m_bookCode, 1, 0, 1, 4);
    this->bookLayout->addWidget(this->m_author, 2, 0, 1, 4);
    this->bookLayout->addWidget(this->m_publishing, 3, 0, 1, 4);
    this->bookLayout->addWidget(this->m_category, 4, 0, 1, 4);
    this->bookLayout->addWidget(this->m_price, 5, 0, 1, 4);
    this->bookLayout->addWidget(this->m_dateIn, 6, 0, 1, 4);
    this->bookLayout->addWidget(this->m_quantity_In, 7, 0, 1, 4);
    this->bookLayout->addWidget(this->m_quantity_Out, 8, 0, 1, 4);
    this->bookLayout->addWidget(this->m_quantity, 9, 0, 1, 4);
    this->bookLayout->addWidget(this->m_isBorrow, 10, 0, 1, 4);

    this->bookLayout->addWidget(this->bookName, 0, 4, 1, 5);
    this->bookLayout->addWidget(this->bookCode, 1, 4, 1, 5);
    this->bookLayout->addWidget(this->author, 2, 4, 1, 5);
    this->bookLayout->addWidget(this->publishing, 3, 4, 1, 5);
    this->bookLayout->addWidget(this->category, 4, 4, 1, 5);
    this->bookLayout->addWidget(this->price, 5, 4, 1, 5);
    this->bookLayout->addWidget(this->dateIn, 6, 4, 1, 5);
    this->bookLayout->addWidget(this->quantity_In, 7, 4, 1, 5);
    this->bookLayout->addWidget(this->quantity_Out, 8, 4, 1, 5);
    this->bookLayout->addWidget(this->quantity, 9, 4, 1, 5);
    this->bookLayout->addWidget(this->isBorrow, 10, 4, 1, 5);

    this->bookLayout->addWidget(this->m_lookDetail, 12, 0, 1, 5);
    this->bookLayout->addWidget(this->m_lendBook, 12, 6, 1, 2);

    this->setFixedSize((sysinclude::WIDTH),2*(sysinclude::HEIGHT)+(sysinclude::GRAP));

    this->bookBox->setLayout(this->bookLayout);
}

void BookGroupBox::createConnections()
{
    QObject::connect(this->m_lendBook, SIGNAL(clicked()), this, SLOT(slotBorrow()));
    QObject::connect(this, SIGNAL(signalSelect(QString)), this->lendBook, SLOT(slotSelectBook(QString)));
}

void BookGroupBox::slotBorrow()
{
    QMessageBox::information(this, tr("提醒"), tr("请填写借书时间和还书时间"), "确定", "取消");
    emit signalSelect(this->bookCode->text());
    this->lendBook->show();
}
