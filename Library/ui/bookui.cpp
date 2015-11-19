#include "bookui.h"
#include <QHBoxLayout>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QLabel>
#include <QSqlDriver>
#include "model/uniquebook.h"
#include "model/books.h"
#include "model/borrow.h"
#include "model/user.h"
#include "core/systype.h"
#include "model/bookcategory.h"
#include "core/sysinclude.h"
#include "dao/daobooks.h"
#include "dao/daouniquebook.h"
#include "dao/daoborrow.h"
#include "model/sysenviroment.h"

BookUI::BookUI(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

BookUI::~BookUI()
{

}

void BookUI::initUI()
{
    this->mainTable = new QTableWidget();

    this->m_contentL = new QLabel("内容简介");
    this->m_authorL = new QLabel("作者简介");
    this->m_includeL = new QLabel("本书目录");
    this->m_descrideL = new QLabel("本书书评");
    this->content = new QTextEdit();
    this->author = new QTextEdit();
    this->include = new QTextEdit();
    this->descride = new QTextEdit();

    this->rightLayout = new QVBoxLayout();
    this->rightLayout->addWidget(m_contentL);
    this->rightLayout->addWidget(content);
    this->rightLayout->addWidget(m_authorL);
    this->rightLayout->addWidget(author);
    this->rightLayout->addWidget(m_includeL);
    this->rightLayout->addWidget(include);
    this->rightLayout->addWidget(m_descrideL);
    this->rightLayout->addWidget(descride);

    this->topLayout = new QHBoxLayout();
    this->topLayout->addWidget(mainTable);
    this->topLayout->addLayout(rightLayout);

    this->confirnBtn = new QPushButton("保存");
    this->cancelBtn = new QPushButton("取消");

    this->btnLayout = new QHBoxLayout();
    this->btnLayout->addStretch();
    this->btnLayout->addWidget(cancelBtn);
    this->btnLayout->addWidget(confirnBtn);

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addLayout(this->topLayout);
    this->mainLayout->addLayout(this->btnLayout);
    this->setLayout(mainLayout);
}

bool BookUI::initTable(UniqueBook *uniqueBook)
{
    if (uniqueBook == NULL)
    {
        QMessageBox::warning(this, tr("错误"), tr("编辑功能出错，table初始化不成功！请检查！"), "确定");
        return false;
    }
    this->uniqueBook = uniqueBook;
    QStringList tableRowName;
    tableRowName.append("书名");
    tableRowName.append("图书编号");
    tableRowName.append("作者");
    tableRowName.append("出版社");
    tableRowName.append("图书类型");
    tableRowName.append("图书价格");
    tableRowName.append("入馆日期");
    tableRowName.append("图书数量");
    tableRowName.append("在馆数量");
    tableRowName.append("是否借出");
    tableRowName.append("读者编号");
    tableRowName.append("借出时间");
    tableRowName.append("应还时间");
    tableRowName.append("是否丢失");

    QStringList tableColumnName;
    tableColumnName.append("名字");
    tableColumnName.append("对应值");

    this->typeBox = new QComboBox();
    int index;
    QList<BookCateGory*> bookCateGoryList = SYSTYPE->getAllBookCateGory();

    Books *book = SYSTYPE->getBook(uniqueBook->getBookId());
    if (book == NULL)
    {
        QMessageBox::warning(this, tr("警告"), tr("编辑操作发生错误！"), "确定");

        return false;
    }
    int bookType = book->getCateGoryId();

    for (int i = 0; i < bookCateGoryList.size(); ++i)
    {
        typeBox->addItem(bookCateGoryList.at(i)->getCateGoryName(),
                            bookCateGoryList.at(i)->getCateGoryId());
        if (bookCateGoryList.at(i)->getCateGoryId() == bookType)
        {
            index = i;
        }
    }
    typeBox->setCurrentIndex(index);


    this->mainTable->setRowCount(tableRowName.size());
    this->mainTable->setColumnCount(tableColumnName.size());
    this->mainTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < tableRowName.size(); ++i)
    {
        this->mainTable->setItem(i, 0, new QTableWidgetItem(tableRowName.at(i)));
    }

    this->mainTable->setItem(0, 1, new QTableWidgetItem(book->getBookName()));
    this->mainTable->setItem(1, 1, new QTableWidgetItem(uniqueBook->getBookCode()));
    this->mainTable->setItem(2, 1, new QTableWidgetItem(book->getAuthor()));
    this->mainTable->setItem(3, 1, new QTableWidgetItem(book->getPublishing()));

    this->mainTable->setCellWidget(4, 1, typeBox);
    this->mainTable->setItem(5, 1, new QTableWidgetItem(book->getPrice()));
    this->mainTable->setItem(6, 1, new QTableWidgetItem(book->getdateIN().toString("yyyy-MM-dd")));
    this->mainTable->setItem(7, 1, new QTableWidgetItem(QString::number(book->getQuantity())));
    this->mainTable->setItem(8, 1, new QTableWidgetItem(QString::number(book->getQuantityIn())));
    if (uniqueBook->getIsBorrow() == sysinclude::yesBorrow)
    {
        this->mainTable->setItem(9, 1, new QTableWidgetItem("是"));
        Borrow *borrow = SYSTYPE->getBorrowByUniqueBook(uniqueBook->getId());
        if (borrow == NULL)
        {
            QMessageBox::warning(this, tr("警告"), tr("编辑操作发生错误！请检查数据库数据"), "确定");
            return false;
        }
        User *user = SYSTYPE->getUser(borrow->getReaderId());
        this->mainTable->setItem(10, 1, new QTableWidgetItem(user->getUserCode()));
        this->mainTable->setItem(11, 1, new QTableWidgetItem(borrow->getDateBorrow().toString("yyyy-MM-dd")));
        this->mainTable->setItem(12, 1, new QTableWidgetItem(borrow->getDateReturn().toString("yyyy-MM-dd")));
        if (borrow->isLoss() == sysinclude::yesLoss)
            this->mainTable->setItem(13, 1, new QTableWidgetItem("是"));
        else
            this->mainTable->setItem(13, 1, new QTableWidgetItem("否"));
    }
    else
    {
        this->mainTable->setItem(9, 1, new QTableWidgetItem("否"));
        this->mainTable->setItem(10, 1, new QTableWidgetItem(""));
        this->mainTable->setItem(11, 1, new QTableWidgetItem(""));
        this->mainTable->setItem(12, 1, new QTableWidgetItem(""));
        this->mainTable->setItem(13, 1, new QTableWidgetItem(""));
    }

    return true;
}

void BookUI::createConnections()
{
    QObject::connect(this->cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(this->confirnBtn, SIGNAL(clicked()), this, SLOT(slotSaveEdit()));
}

QVector<QString> BookUI::getBookInfo()
{
    QVector<QString> bookInfoVec;
    for (int i = 0; i < this->mainTable->rowCount(); ++i)
    {
        if (i != 4)
        {
            bookInfoVec.append(this->mainTable->item(i, 1)->text());
        }
        else
        {
            QString type = this->typeBox->itemData(this->typeBox->currentIndex(),
                                                   Qt::UserRole).toString();
            bookInfoVec.append(type);
        }
    }
    return bookInfoVec;
}

void BookUI::slotSaveEdit()
{
    this->confirnBtn->setDisabled(true);
    QVector<QString> bookInfoVec = this->getBookInfo();

    if (bookInfoVec.at(7).toInt() < bookInfoVec.at(8).toInt())
    {
        QMessageBox::warning(this, tr("警告"), tr("在馆数量大于图书数量，请仔细检查"), "确定");
        this->confirnBtn->setDisabled(false);
        return;
    }

    User *user = NULL;
    if (bookInfoVec.at(9) == "是")
    {
        QString userCode = bookInfoVec.at(10);
        user = SYSTYPE->getUserByCode(userCode);
        if (user == NULL)
        {
            QMessageBox::warning(this, tr("警告"), tr("不存在该读者，请仔细检查"), "确定");
            this->confirnBtn->setDisabled(false);
            return;
        }
    }

    Books *book = SYSTYPE->getBook(this->uniqueBook->getBookId());
    if (book == NULL)
    {
        this->confirnBtn->setDisabled(false);
        return;
    }
    book->setBookName(bookInfoVec.at(0));
    book->setAuthor(bookInfoVec.at(2));
    book->setPublishing(bookInfoVec.at(3));
    book->setCateGoryId(bookInfoVec.at(4).toInt());
    book->setPrice(bookInfoVec.at(5));
    book->setdateIN(QDate::fromString(bookInfoVec.at(6), "yyyy-MM-dd"));
    book->setQuantity(bookInfoVec.at(7).toInt());
    book->setQuantityIn(bookInfoVec.at(8).toInt());
    book->setQuantityOut(bookInfoVec.at(7).toInt() - bookInfoVec.at(8).toInt());

    this->uniqueBook->setBookCode(bookInfoVec.at(1));

    int isBorrow = this->uniqueBook->getIsBorrow();   
    Borrow *borrow = NULL;
    if (isBorrow == sysinclude::yesBorrow)
    {
        borrow= SYSTYPE->getBorrowByUniqueBook(this->uniqueBook->getId());
        if (borrow == NULL)
        {
            QMessageBox::warning(this, tr("警告"), tr("数据出错，无法保存，请关闭"), "确定");
            this->confirnBtn->setEnabled(true);
            return;
        }
    }

    if (bookInfoVec.at(9) == "是")
        this->uniqueBook->setIsBorrow(sysinclude::yesBorrow);
    else
        this->uniqueBook->setIsBorrow(sysinclude::noBorrow);

    DaoBorrow daoBorrow;
    DaoUniqueBook daoUniqueBook;
    DaoBooks daoBook;

    if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions))
    {
        if (GLobal_DB->transaction())
        {
            bool retBook = daoBook.Update(book);
            bool retUnique = daoUniqueBook.Update(uniqueBook);
            if (retBook == false || retUnique == false)
            {
                if(GLobal_DB->rollback())
                {
                    SYSTYPE->reverBook(book->getBookId());
                    SYSTYPE->reverUniqueBook(uniqueBook->getId());
                    QMessageBox::information(this, tr("提醒"), tr("更新失败！"), "确定");
                    this->confirnBtn->setDisabled(false);
                    return;
                }
            }

            bool borrowRet = false;

            if(isBorrow == sysinclude::yesBorrow)
            {
                if (bookInfoVec.at(9) == "是")
                {
                    borrow->setReaderId(user->getUserID());
                    borrow->setDateBorrow(QDate::fromString(bookInfoVec.at(11), "yyyy-MM-dd"));
                    borrow->setDateReturn(QDate::fromString(bookInfoVec.at(12), "yyyy-MM-dd"));
                    if (bookInfoVec.at(13) == "是")
                        borrow->setLoss(sysinclude::yesLoss);
                    else
                        borrow->setLoss(sysinclude::noLoss);
                    borrowRet = daoBorrow.Update(borrow);
                }
                else
                {
                    borrowRet = daoBorrow.Delete(borrow);
                }
                if (borrowRet == false)
                {
                    if(GLobal_DB->rollback())
                    {
                        SYSTYPE->reverBook(book->getBookId());
                        SYSTYPE->reverUniqueBook(uniqueBook->getId());
                        SYSTYPE->reverBorrow(borrow->getBorrowId());
                        QMessageBox::information(this, tr("提醒"), tr("更新失败！"), "确定");
                        this->confirnBtn->setDisabled(false);
                        return;
                    }
                }

            }

            else
            {
                if (bookInfoVec.at(9) == "是")
                {
                    Borrow *newBorrow = new Borrow();
                    newBorrow->setReaderId(user->getUserID());
                    newBorrow->setBookId(this->uniqueBook->getId());
                    newBorrow->setDateBorrow(QDate::fromString(bookInfoVec.at(11), "yyyy-MM-dd"));
                    newBorrow->setDateReturn(QDate::fromString(bookInfoVec.at(12), "yyyy-MM-dd"));
                    if (bookInfoVec.at(13) == "是")
                        newBorrow->setLoss(sysinclude::yesLoss);
                    else
                        newBorrow->setLoss(sysinclude::noLoss);
                    borrowRet = daoBorrow.Add(newBorrow);

                    BaseDao basedao;
                    QString tableName = "BORROW";
                    QString outFields = "ID";
                    int borrowId = basedao.getId(tableName, outFields);
                    newBorrow->setBorrowId(borrowId);

                    if (borrowRet == false)
                    {
                        GLobal_DB->rollback();
                        SYSTYPE->reverBook(book->getBookId());
                        SYSTYPE->reverUniqueBook(uniqueBook->getId());
                        QMessageBox::information(this, tr("提醒"), tr("更新失败！"), "确定");
                        this->confirnBtn->setEnabled(true);
                        return;
                    }
                    SYSTYPE->addBorrow(newBorrow->getBorrowId(), newBorrow);
                }
            }

            if (GLobal_DB->commit())
            {
                QMessageBox::information(this, tr("提醒"), tr("更新成功！"), "确定");
                this->confirnBtn->setEnabled(true);
            }
        }
    }
}
