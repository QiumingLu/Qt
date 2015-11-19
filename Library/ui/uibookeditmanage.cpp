#include "uibookeditmanage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSql>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include "ui/newbookui.h"
#include "model/books.h"
#include "model/uniquebook.h"
#include "dao/daobooks.h"
#include "dao/daouniquebook.h"
#include "core/sysinclude.h"
#include "dao/DaoHeader.h"
#include "model/sysenviroment.h"
#include "core/systype.h"

UIBookEditManage::UIBookEditManage(QWidget *parent):
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIBookEditManage::~UIBookEditManage()
{

}

void UIBookEditManage::initUI()
{
    this->newBookUI = new NewBookUI();
    this->topLayout = new QHBoxLayout();
    this->mainLayout = new QVBoxLayout();

    this->confirnBtn = new QPushButton("保存");
    this->cancelBtn = new QPushButton("取消");

    this->btnLayout = new QHBoxLayout();
    this->btnLayout->addStretch();
    this->btnLayout->addWidget(cancelBtn);
    this->btnLayout->addWidget(confirnBtn);

    this->topLayout->addWidget(newBookUI);
    this->mainLayout->addLayout(topLayout);
    this->mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);
}

void UIBookEditManage::createConnections()
{
    QObject::connect(this->cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancel()));
    QObject::connect(this->confirnBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
}

void UIBookEditManage::slotCancel()
{
    int ret = QMessageBox::warning(this, tr("警告"), tr("是否取消所做的修改？"), "确定", "取消");
    if (ret == 1)
    {
        return ;
    } else{
        this->hide();
    }
}

void UIBookEditManage::slotSave()
{
    QVector<QString> bookInfoVec = this->newBookUI->getBookInfo();
    Books *book = new Books();
    QVector<UniqueBook*> uniqueBookVec;

    book->setBookName(bookInfoVec.at(0));
    book->setAuthor(bookInfoVec.at(1));
    book->setPublishing(bookInfoVec.at(2));
    book->setCateGoryId(bookInfoVec.at(3).toInt());
    book->setPrice(bookInfoVec.at(4));
    book->setdateIN(QDate::fromString(bookInfoVec.at(5), "yyyy-MM-dd"));
    book->setQuantity(bookInfoVec.at(6).toInt());
    book->setQuantityIn(bookInfoVec.at(6).toInt());
    QStringList bookCodeList  = bookInfoVec.at(7).split(",");
    book->setQuantityOut(0);

    if (bookCodeList.size() != book->getQuantity())
    {
        QMessageBox::warning(this, tr("警告"), tr("图书数量和编号数量不一致！请检查！"), "确定");
        return;
    }

    DaoBooks daoBook;
    BaseDao basedao;

    if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
    {
        if (QSqlDatabase::database().transaction())
        {
            bool ret = daoBook.Add(book);

            QString tableName = "BOOKS";
            QString outFields =  "BOOK_ID";
            int bookId = basedao.getId(tableName, outFields);
            book->setBookId(bookId);

            if (ret)
            {
                DaoUniqueBook daoUniqueBook;

                foreach(QString bookCode, bookCodeList)
                {
                    UniqueBook *uniqueBook = new UniqueBook();
                    uniqueBook->setBookId(book->getBookId());
                    uniqueBook->setBookCode(bookCode);
                    uniqueBook->setIsBorrow(sysinclude::noBorrow);
                    bool flags = daoUniqueBook.Add(uniqueBook);
                    if (flags == false)
                    {
                        QMessageBox::warning(this, tr("警告"), tr("保存失败"), "确定");
                        QSqlDatabase::database().rollback();
                        return;
                    }
                    QString uniqueBookTable = "UNIQUE_BOOK";
                    QString uniqueBookId = "ID";
                    int id = basedao.getId(uniqueBookTable, uniqueBookId);
                    uniqueBook->setId(id);
                    uniqueBookVec.append(uniqueBook);
                }

            } else {
                QMessageBox::warning(this, tr("警告"), tr("保存失败"), "确定");
                QSqlDatabase::database().rollback();
                return;
            }

            if (QSqlDatabase::database().commit())
            {
                 QMessageBox::warning(this, tr("提醒"), tr("保存成功！"), "确定");

                 SYSTYPE->addBook(book->getBookId(), book);
                 foreach (UniqueBook *uniqueBook, uniqueBookVec)
                 {
                     SYSTYPE->addUniqueBook(uniqueBook->getId(), uniqueBook);
                 }

            } else {
                QMessageBox::warning(this, tr("警告"), tr("保存失败"), "确定");
            }
        }
    }
}
