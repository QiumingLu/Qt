#include "mylibrarybox.h"
#include "core/sysinclude.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include "core/systype.h"
#include "model/uniquebook.h"
#include "model/borrow.h"
#include "core/sysinclude.h"
#include "dao/DaoHeader.h"
#include "dao/daoborrow.h"
#include "dao/daouniquebook.h"

MyLibraryBox::MyLibraryBox(QWidget *parent) :
    QWidget(parent)

{
    this->initUI();
    this->createConnections();
}

MyLibraryBox::~MyLibraryBox()
{
}

void MyLibraryBox::initUI()
{
    this->borrowBox = new QGroupBox(this);
    this->borrowLayout = new QGridLayout(this);

    this->bookName = new QLabel(this);
    this->bookCode = new QLabel(this);
    this->author = new QLabel(this);
    this->publishing = new QLabel(this);
    this->category = new QLabel(this);
    this->price = new QLabel(this);
    this->dateIn = new QLabel(this);
    this->dateBorrow = new QLabel(this);
    this->dateReturn = new QLabel(this);
    this->isloss = new QLabel(this);

    this->m_bookName = new QLabel("书名：", this);
    this->m_bookCode = new QLabel("图书编号：", this);
    this->m_author = new QLabel("作者：", this);
    this->m_publishing = new QLabel("出版社：", this);
    this->m_category = new QLabel("类别：", this);
    this->m_price = new QLabel("定价：", this);
    this->m_dateIn = new QLabel("入馆时间：", this);
    this->m_dateBorrow = new QLabel("借书时间：", this);
    this->m_dateReturn = new QLabel("还书时间：",this);
    this->m_isloss = new QLabel("是否丢失", this);

    this->m_loss = new QPushButton(tr("挂失"));
    this->m_returnBook = new QPushButton(tr("还书"));

    borrowLayout->addWidget(this->m_bookName, 0, 0, 1, 4);
    borrowLayout->addWidget(this->m_bookCode, 1, 0, 1, 4);
    borrowLayout->addWidget(this->m_author, 2, 0, 1, 4);
    borrowLayout->addWidget(this->m_publishing, 3, 0, 1, 4);
    borrowLayout->addWidget(this->m_category, 4, 0, 1, 4);
    borrowLayout->addWidget(this->m_price, 5, 0, 1, 4);
    borrowLayout->addWidget(this->m_dateIn, 6, 0, 1, 4);
    borrowLayout->addWidget(this->m_dateBorrow, 7, 0, 1, 4);
    borrowLayout->addWidget(this->m_dateReturn, 8, 0, 1, 4);
    borrowLayout->addWidget(this->m_isloss, 9, 0, 1, 4);

    borrowLayout->addWidget(this->bookName, 0, 4, 1, 5);
    borrowLayout->addWidget(this->bookCode, 1, 4, 1, 5);
    borrowLayout->addWidget(this->author, 2, 4, 1, 5);
    borrowLayout->addWidget(this->publishing, 3, 4, 1, 5);
    borrowLayout->addWidget(this->category, 4, 4, 1, 5);
    borrowLayout->addWidget(this->price, 5, 4, 1, 5);
    borrowLayout->addWidget(this->dateIn, 6, 4, 1, 5);
    borrowLayout->addWidget(this->dateBorrow, 7, 4, 1, 5);
    borrowLayout->addWidget(this->dateReturn, 8, 4, 1, 5);
    borrowLayout->addWidget(this->isloss, 9, 4, 1, 5);

    borrowLayout->addWidget(this->m_loss, 10, 1, 1, 3);
    borrowLayout->addWidget(this->m_returnBook, 10, 5, 1, 3);

    this->setFixedSize((sysinclude::WIDTH),2*(sysinclude::HEIGHT)+(sysinclude::GRAP));
    borrowBox->setLayout(borrowLayout);
}

void MyLibraryBox::createConnections()
{
    QObject::connect(this->m_loss, SIGNAL(clicked()), this, SLOT(slotLoss()));
    QObject::connect(this->m_returnBook, SIGNAL(clicked()), this, SLOT(slotReturn()));
}

void MyLibraryBox::slotLoss()
{
    QString bookCode = this->bookCode->text();
    UniqueBook* uniqueBook = SYSTYPE->getUniqueBookByBookCode(bookCode);
    Borrow* borrow = SYSTYPE->getBorrowByUniqueBook(uniqueBook->getId());
    Q_ASSERT(borrow != NULL);

    DaoBorrow daoBorrow;
    bool ret;

    if (this->m_loss->text() == "挂失")
    {
        borrow->setLoss(sysinclude::yesLoss);
        ret = daoBorrow.Update(borrow);

        if (ret == true)
        {
            QMessageBox::information(this, tr("挂失"), tr("挂失成功！"), tr("确定"));
            this->m_returnBook->setDisabled(true);
            this->isloss->text().clear();
            this->m_loss->text().clear();
            this->isloss->setText("是");
            this->m_loss->setText("取消挂失");
        }
        else
        {
            QMessageBox::information(this, tr("挂失"), tr("挂失失败！"), tr("确定"));
            borrow->setLoss(sysinclude::noLoss);
        }
    }
    else
    {
        borrow->setLoss(sysinclude::noLoss);
        ret = daoBorrow.Update(borrow);
        if (ret == true)
        {
            QMessageBox::information(this, tr("取消挂失"), tr("取消成功！"), tr("确定"));
            this->m_returnBook->setDisabled(false);
            this->isloss->text().clear();
            this->m_loss->text().clear();
            this->isloss->setText("否");
            this->m_loss->setText("挂失");
        }
        else
        {
            QMessageBox::information(this, tr("取消挂失"), tr("取消失败！"), tr("确定"));
            borrow->setLoss(sysinclude::yesLoss);
        }
    }
}

void MyLibraryBox::slotReturn()
{
    bool retBorrow;
    bool retUniqueBook;
    QString bookCode = this->bookCode->text();
    UniqueBook* uniqueBook = SYSTYPE->getUniqueBookByBookCode(bookCode);
    Borrow* borrow = SYSTYPE->getBorrowByUniqueBook(uniqueBook->getId());
    if (borrow != NULL)
    {
        if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
        {
            if (QSqlDatabase::database().transaction())
            {
                DaoBorrow daoBorrow;
                DaoUniqueBook daoUniqueBook;
                retBorrow = daoBorrow.Delete(borrow);
                uniqueBook->setIsBorrow(sysinclude::noBorrow);
                retUniqueBook = daoUniqueBook.Update(uniqueBook);
                QDate currentTime = QDate::currentDate();

                if (retBorrow == false || retUniqueBook == false)
                {
                    QSqlDatabase::database().rollback();
                    SYSTYPE->reverUniqueBook(uniqueBook->getId());
                    QMessageBox::information(this, tr("还书"), tr("还书失败！"), tr("确定"));
                }

                if (QSqlDatabase::database().commit())
                {
                    QMessageBox::information(this, tr("还书"), tr("还书成功！"), tr("确定"));
                    this->dateReturn->setText(currentTime.toString());
                    this->m_returnBook->setDisabled(true);
                    this->m_loss->setDisabled(true);
                    SYSTYPE->deleteBorrow(borrow->getBorrowId());
                }
                else
                {
                    QMessageBox::information(this, tr("还书"), tr("还书失败！"), tr("确定"));
                }
            }
        }
    }
}
