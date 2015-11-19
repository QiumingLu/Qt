#include "uilendbook.h"
#include <QDateEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDriver>
#include <QSqlDatabase>
#include "model/sysenviroment.h"
#include "model/readers.h"
#include "core/systype.h"
#include "core/sysinclude.h"
#include "model/memberlevel.h"
#include "model/uniquebook.h"
#include "dao/DaoHeader.h"
#include "dao/daouniquebook.h"
#include "dao/daoborrow.h"
#include "model/borrow.h"
#include "model/books.h"
#include "dao/daobooks.h"

UILendBook::UILendBook(QWidget *parent) :
    QWidget(parent)
{
    this->reader = SysEnviroment::getInstance()->getReader();
    this->initUI();
    this->createConnections();
}

UILendBook::~UILendBook()
{
    SAFE_DELETE(m_level);
    SAFE_DELETE(m_day);
    SAFE_DELETE(m_lendBooks);
    SAFE_DELETE(m_lendBookNum);
    SAFE_DELETE(m_lendTime);
    SAFE_DELETE(m_returnTime);

    SAFE_DELETE(level);
    SAFE_DELETE(day);
    SAFE_DELETE(lendBooks);
    SAFE_DELETE(lendBookNum);
    SAFE_DELETE(lendTime);
    SAFE_DELETE(returnTime);

    SAFE_DELETE(confirmBtn);
    SAFE_DELETE(cancelBtn);
    SAFE_DELETE(mainLayout);
}

void UILendBook::initUI()
{
    this->m_level = new QLabel("您的会员级别是：");
    this->m_day = new QLabel("最长的借书时间：");
    this->m_lendBooks = new QLabel("最多可以借书的数量为：");
    this->m_lendBookNum = new QLabel("还可以借书的数量为：");
    this->m_lendTime = new QLabel("借书时间：");
    this->m_returnTime = new QLabel("还书时间：");

    this->level = new QLabel();
    this->day = new QLabel();
    this->lendBooks = new QLabel();
    this->lendBookNum = new QLabel();
    this->lendTime = new QLabel();
    this->returnTime = new QDateEdit();

    this->confirmBtn = new QPushButton("确定");
    this->cancelBtn = new QPushButton("取消");

    Q_ASSERT(reader != NULL);
    this->level->setText(QString::number(this->reader->getCardLevel()));
    MemberLevel* memberLevel = SYSTYPE->getMemberLevel(this->reader->getCardLevel());
    this->day->setText(QString::number(memberLevel->getDays()));
    this->lendBooks->setText(QString::number(memberLevel->getNumbers()));

    QVector<Borrow*> borrowBooks = SYSTYPE->getReaderBorrow(this->reader->getReaderId());
    int borrowSize = (memberLevel->getNumbers() - borrowBooks.size());
    this->lendBookNum->setText(QString::number(borrowSize));

    this->lendTime->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    qint64 days = memberLevel->getDays();
    this->returnTime->setDateRange(QDate::currentDate(),
                                   QDate::currentDate().addDays(days));
    this->returnTime->setDisplayFormat("yyyy-MM-dd");
    if (borrowSize <= 0)
    {
        this->confirmBtn->setDisabled(true);
    }

    this->mainLayout = new QGridLayout(this);
    this->mainLayout->addWidget(this->m_level, 0, 0, 1, 5);
    this->mainLayout->addWidget(this->m_day, 1, 0, 1, 5);
    this->mainLayout->addWidget(this->m_lendBooks, 2, 0, 1, 5);
    this->mainLayout->addWidget(this->m_lendBookNum, 3, 0, 1, 5);
    this->mainLayout->addWidget(this->m_lendTime, 4, 0, 1, 5);
    this->mainLayout->addWidget(this->m_returnTime, 5, 0, 1, 5);

    this->mainLayout->addWidget(this->level, 0, 5, 1, 5);
    this->mainLayout->addWidget(this->day, 1, 5, 1, 5);
    this->mainLayout->addWidget(this->lendBooks, 2, 5, 1, 5);
    this->mainLayout->addWidget(this->lendBookNum, 3, 5, 1, 5);
    this->mainLayout->addWidget(this->lendTime, 4, 5, 1, 5);
    this->mainLayout->addWidget(this->returnTime, 5, 5, 1, 5);

    this->mainLayout->addWidget(this->cancelBtn, 6, 2, 1, 3);
    this->mainLayout->addWidget(this->confirmBtn, 6, 6, 1, 3);
    this->setLayout(mainLayout);
    this->setFixedSize(500, 350);
}

void UILendBook::createConnections()
{
    QObject::connect(this->cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->confirmBtn, SIGNAL(clicked()), this, SLOT(slotLendBook()));
}

void UILendBook::slotLendBook()
{
    if (this->bookCode != "")
    {
        UniqueBook* uniqueBook = SYSTYPE->getUniqueBookByBookCode(this->bookCode);
        Q_ASSERT(uniqueBook != NULL);
        uniqueBook->setIsBorrow(sysinclude::yesBorrow);
        int userId = SysEnviroment::getInstance()->getUser()->getUserID();
        QDate borrowDate = QDate::currentDate();
        QDate returnDate = QDate::fromString(this->returnTime->text(), "yyyy-MM-dd");
        Borrow *borrow = new Borrow();
        borrow->setReaderId(userId);
        borrow->setBookId(uniqueBook->getId());
        borrow->setDateBorrow(borrowDate);
        borrow->setDateReturn(returnDate);
        borrow->setLoss(sysinclude::noLoss);

        Books* book = SYSTYPE->getBook(uniqueBook->getBookId());
        int quantityIn = book->getQuantityIn() - 1;
        int quantityOut = book->getQuantityOut() + 1;
        book->setQuantityIn(quantityIn);
        book->setQuantityOut(quantityOut);

        if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
        {
            if (QSqlDatabase::database().transaction())
            {
                DaoBorrow daoBorrow;
                DaoUniqueBook daoUniqueBook;
                DaoBooks daoBook;
                bool retBook = daoBook.Update(book);
                bool retUniqueBook = daoUniqueBook.Update(uniqueBook);
                bool retBorrow = daoBorrow.Add(borrow);
                if (retUniqueBook == false || retBook == false || retBorrow == false)
                {
                    QSqlDatabase::database().rollback();
                    QMessageBox::information(this, tr("提醒信息"), tr("借书失败！"), "确定");
                    SYSTYPE->reverBook(book->getBookId());
                    SYSTYPE->reverUniqueBook(uniqueBook->getId());
                    return;
                }

                if (QSqlDatabase::database().commit())
                {
                    QMessageBox::information(this, tr("提醒信息"), tr("借书成功！"), "确定");
                    this->confirmBtn->setDisabled(false);
                    QString tableName = "BORROW";
                    QString outFields = "ID";
                    BaseDao baseDao;
                    int id = baseDao.getId(tableName, outFields);
                    borrow->setBorrowId(id);
                    SYSTYPE->addBorrow(borrow->getBorrowId(), borrow);
                } else {
                    QMessageBox::information(this, tr("提醒信息"), tr("借书失败！"), "确定");
                }
            }
        }
    }
}

void UILendBook::slotSelectBook(QString bookCode)
{
    this->bookCode = bookCode;
}
