#include "uibookinformationmanage.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlError>
#include <set>
#include <QLineEdit>
#include "core/systype.h"
#include "model/bookcategory.h"
#include "model/books.h"
#include "model/uniquebook.h"
#include "core/sysinclude.h"
#include "model/borrow.h"
#include "ui/bookgroupbox.h"
#include "ui/bookui.h"
#include "model/user.h"
#include "dao/daouniquebook.h"
#include "dao/daobooks.h"
#include "dao/daoborrow.h"
#include "model/sysenviroment.h"

UIBookInformationManage::UIBookInformationManage(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->createConnections();
}

UIBookInformationManage::~UIBookInformationManage()
{

}

void UIBookInformationManage::initUI()
{
    this->findBook = new QLineEdit();
    this->findAction = new QPushButton("高级检索");
    this->findBtn = new QHBoxLayout();
    this->findBook->hide();
    this->findAction->hide();
    this->findBtn->addWidget(findBook);
    this->findBtn->addWidget(findAction);
    this->findBtn->addStretch();
    this->bookTable = new QTableWidget();
    this->bookTable->setWindowTitle("书籍管理列表");
    this->bookTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->bookTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList tableColumnName;
    tableColumnName.append("书名");
    tableColumnName.append("图书编号");
    tableColumnName.append("作者");
    tableColumnName.append("出版社");
    tableColumnName.append("是否借出");
    tableColumnName.append("读者编号");
    tableColumnName.append("借出时间");
    tableColumnName.append("应还时间");
    tableColumnName.append("是否丢失");
    tableColumnName.append("详细信息");
    tableColumnName.append("编辑");

    this->bookTable->setColumnCount(tableColumnName.size());
    this->bookTable->setHorizontalHeaderLabels(tableColumnName);

    this->deleteBtn = new QPushButton("删除");
    this->saveBtn = new QPushButton("保存");
    this->closeBtn = new QPushButton("取消");

    this->btnLayout = new QHBoxLayout();
    this->btnLayout->addStretch();
    this->btnLayout->addWidget(this->deleteBtn);
    this->btnLayout->addWidget(this->saveBtn);
    this->btnLayout->addWidget(this->closeBtn);

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addLayout(this->findBtn);
    this->mainLayout->addWidget(this->bookTable);
    this->mainLayout->addLayout(this->btnLayout);
    this->setLayout(mainLayout);
}

void UIBookInformationManage::initEditOldBook()
{
    this->findBook->show();
    this->findAction->show();
}

void UIBookInformationManage::initBookTable(int bookType)
{
    if (bookType != 0)
    {
        this->uniqueBookVec = SYSTYPE->getUniqueBookByType(bookType);
    }

    this->bookTable->setRowCount(uniqueBookVec.size());
    int row = this->bookTable->rowCount();

    for (int i = 0; i < row; ++i)
    {
        Books *book = SYSTYPE->getBook(uniqueBookVec.at(i)->getBookId());
        this->bookTable->setItem(i, 0, new QTableWidgetItem(book->getBookName()));
        this->bookTable->setItem(i, 1, new QTableWidgetItem(uniqueBookVec.at(i)->getBookCode()));
        this->bookTable->setItem(i, 2, new QTableWidgetItem(book->getAuthor()));
        this->bookTable->setItem(i, 3, new QTableWidgetItem(book->getPublishing()));
        if (uniqueBookVec.at(i)->getIsBorrow() == sysinclude::yesBorrow)
        {
            this->bookTable->setItem(i, 4, new QTableWidgetItem("是"));

            Borrow *borrow = SYSTYPE->getBorrowByUniqueBook(uniqueBookVec.at(i)->getId());
            if (borrow == NULL)
            {
                QMessageBox::information(this, tr("警告"), tr("出现错误！"), "确定");
                return;
            }
            User *user = SYSTYPE->getUser(borrow->getReaderId());
            this->bookTable->setItem(i, 5, new QTableWidgetItem(user->getUserCode()));
            this->bookTable->setItem(i, 6, new QTableWidgetItem(borrow->getDateBorrow().toString("yyyy-MM-dd")));
            this->bookTable->setItem(i, 7, new QTableWidgetItem(borrow->getDateReturn().toString("yyyy-MM-dd")));
            if (borrow->isLoss() == sysinclude::yesLoss)
                this->bookTable->setItem(i, 8, new QTableWidgetItem("是"));
            else
                this->bookTable->setItem(i, 8, new QTableWidgetItem("否"));

        } else {
            this->bookTable->setItem(i, 4, new QTableWidgetItem("否"));
            this->bookTable->setItem(i, 8, new QTableWidgetItem("否"));
        }

        QPushButton *buttonDetail = new QPushButton();
        buttonDetail->setText("详细信息");
        buttonDetail->setEnabled(true);

        QPushButton *buttonEdit = new QPushButton();
        buttonEdit->setText("编辑");
        buttonEdit->setEnabled(true);

        this->bookTable->setCellWidget(i, 9, buttonDetail);
        this->bookTable->setCellWidget(i, 10, buttonEdit);

        QObject::connect(buttonEdit, SIGNAL(clicked()), this, SLOT(slotEdit()));
        QObject::connect(buttonDetail, SIGNAL(clicked()), this, SLOT(slotDetail()));
    }
}

void UIBookInformationManage::createConnections()
{
    QObject::connect(this->findAction, SIGNAL(clicked()), this, SLOT(slotFindBook()));
    QObject::connect(this->deleteBtn, SIGNAL(clicked()), this, SLOT(slotDelete()));
    QObject::connect(this->saveBtn, SIGNAL(clicked()), this, SLOT(slotSave()));
    QObject::connect(this->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void UIBookInformationManage::slotFindBook()
{
    DaoBooks daoBook;
    QString inputBook = this->findBook->text();
    QVector<Books*> findBookVec = daoBook.findBook(inputBook);
    this->uniqueBookVec.clear();
    foreach (Books *book, findBookVec)
    {
        QVector<UniqueBook*> uniqueVec = SYSTYPE->getUniqueBookByBookId(book->getBookId());
        this->uniqueBookVec += uniqueVec;
    }
    int bookType = 0;
    this->initBookTable(bookType);
}

void UIBookInformationManage::slotDetail()
{
    this->bookTable->setFocus();
    int row = -1;
    row = this->bookTable->currentRow();
    if (row >= 0)
    {
        return;
    }
}

void UIBookInformationManage::slotEdit()
{
    this->bookTable->setFocus();
    int row = -1;
    row = this->bookTable->currentRow();  //获取当前行
    if (row >= 0)
    {
        int ret = QMessageBox::information(this, tr("information"), tr("启动编辑？"), "确定", "取消");
        if (ret == 1)
            return ;
        this->bookUI = new BookUI();
        UniqueBook *uniqueBook = uniqueBookVec.at(row);
        if (this->bookUI->initTable(uniqueBook))
            this->bookUI->show();
        else
            return;
    }
}

void UIBookInformationManage::slotDelete()
{
    QList<QTableWidgetItem*> deleteList = this->bookTable->selectedItems();  //读取所有被选中的item
    if (deleteList.size() == 0)
    {
        QMessageBox::information(this, tr("提醒"), tr("请选择要删除的行"));
        return;
    }

    int ret = QMessageBox::warning(this, tr("警告"), tr("确定要删除所选中的行？"), "确定", "取消");
    if (ret == 1)
        return;

    std::set<int> del_row;              //记录要删除的行号，用set防止重复
    for (int i = 0; i < deleteList.size(); ++i)       //删除选中的项
    {
        QTableWidgetItem *selectItem = deleteList.at(i);   //指向选中的item的指针
        if (selectItem)
        {
            int row = this->bookTable->row(selectItem);    //获取行号
            del_row.insert(row);
        }
    }

    std::vector<int> del_list;
    for (std::set<int>::iterator it = del_row.begin(); it != del_row.end(); ++it)
    {
        del_list.push_back(*it);
    }

    for (int i = del_list.size() - 1; i >= 0; i--)
    {
        UniqueBook *uniqueBook = this->uniqueBookVec.at(del_list.at(i));
        Borrow *borrow = SYSTYPE->getBorrowByUniqueBook(uniqueBook->getId());
        Books *book = SYSTYPE->getBook(uniqueBook->getBookId());

        DaoUniqueBook daoUniqueBook;
        DaoBooks daoBook;
        BaseDao basedao;

        if (borrow != NULL)
        {
            int ret = QMessageBox::warning(this, tr("警告"),
                                           "第" + QString::number(del_list.at(i) + 1) + "行的书已被借出，确定删除？", "确定", "取消");
            if (ret == 1)
                continue;
        }
        if (QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)) //先判断数据库是否支持事物操作
        {
            if(basedao.transaction())  //启动事物操作
            {
                bool uniuqeBookRet = true;
                bool bookRet;

                if (book->getQuantity() == 1)
                {
                    bookRet = daoBook.Delete(book);
                }
                else
                {
                    int quantity = book->getQuantity() - 1;
                    if (borrow != NULL)
                    {
                        int quantityOut = book->getQuantityOut() - 1;
                        book->setQuantity(quantity);
                        book->setQuantityOut(quantityOut);
                    }
                    else
                    {
                        int quantityIn = book->getQuantityIn() - 1;
                        book->setQuantity(quantity);
                        book->setQuantityIn(quantityIn);
                    }
                    bookRet = daoBook.Update(book);
                    uniuqeBookRet = daoUniqueBook.Delete(uniqueBook);
                }

                if (bookRet == false || uniuqeBookRet == false)
                {
                    QMessageBox::warning(this, tr("警告"), "第" + QString::number(del_list.at(i) + 1) + "删除失败！", "确定");
                    QSqlDatabase::database().rollback();
                    return;
                }

                if (basedao.commit())
                {
                    this->bookTable->removeRow(del_list.at(i));
                    QMessageBox::warning(this, tr("提醒"), "第" +QString::number(del_list.at(i) + 1) +"删除成功！", "确定");
                    SYSTYPE->reverBook(book->getBookId());
                    SYSTYPE->reverUniqueBook(uniqueBook->getId());
                    if (borrow != NULL)
                    {
                        SYSTYPE->reverBorrow(borrow->getBorrowId());
                    }

                    this->uniqueBookVec.remove(del_list.at(i));
                } else {
                    qDebug() << GLobal_DB->lastError();
                    QMessageBox::warning(this, tr("警告"), "第" + QString::number(del_list.at(i) + 1) + "删除失败！", "确定");
                }
            }
        }
    }
}

void UIBookInformationManage::slotSave()
{
    int ret = QMessageBox::information(this, tr("information"), tr("确定保存所修改的内容？"), "确定", "取消");
    if (ret == 0)
    {
    }
    else
        return;
}
