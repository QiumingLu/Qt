#include "addbookcategory.h"
#include <QPushButton>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "model/bookcategory.h"
#include "dao/daobookcategory.h"
#include "core/systype.h"

AddBookCateGory::AddBookCateGory(QWidget *parent) :
    AddBaseWidget(parent)
{
    this->bookCateGory = NULL;
    this->initTable();
}

AddBookCateGory::~AddBookCateGory()
{
}

void AddBookCateGory::initTable()
{
    QStringList tableColumnName;
    tableColumnName.append("类型名");
    tableColumnName.append("备注");

    this->mainTable->setColumnCount(tableColumnName.size());
    this->mainTable->setHorizontalHeaderLabels(tableColumnName);
    this->mainTable->setRowCount(1);
    this->mainTable->setItem(0, 0, new QTableWidgetItem());
    this->mainTable->setItem(0, 1, new QTableWidgetItem());
}

QVector<QString> AddBookCateGory::getTableText() const
{
    QVector<QString> bookCateGoryVec;
    bookCateGoryVec.append(this->mainTable->item(0, 0)->text());
    bookCateGoryVec.append(this->mainTable->item(0, 1)->text());
    return bookCateGoryVec;
}

void AddBookCateGory::slotSave()
{
    QVector<QString> bookCateGoryVec = this->getTableText();
    if (this->bookCateGory == NULL)
    {
        this->bookCateGory = new BookCateGory();
        this->bookCateGory->setCateGoryName(bookCateGoryVec.at(0));
        DaoBookCateGory daoBookCateGory;
        bool ret = daoBookCateGory.Add(this->bookCateGory);
        QString tableName = "BOOK_CATEGORY";
        QString outFields = "CATEGORY_ID";
        BaseDao baseDao;
        int id = baseDao.getId(tableName, outFields);
        if (ret)
        {
            QMessageBox::information(this, tr("提醒"), "保存成功", "确定");
            SYSTYPE->addBookCateGory(id, bookCateGory);
        }
    }
}
