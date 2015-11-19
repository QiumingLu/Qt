#include "newbookui.h"
#include <QHBoxLayout>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QLabel>
#include <QDate>
#include "core/systype.h"
#include "core/sysinclude.h"
#include "model/bookcategory.h"

NewBookUI::NewBookUI(QWidget *parent) :
    QWidget(parent)
{
    this->initUI();
    this->initTable();
}

NewBookUI::~NewBookUI()
{

}

void NewBookUI::initUI()
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

    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addLayout(this->topLayout);
    this->setLayout(mainLayout);
}

void NewBookUI::initTable()
{
    QStringList tableRowName;
    tableRowName.append("书名");
    tableRowName.append("作者");
    tableRowName.append("出版社");
    tableRowName.append("图书类型");
    tableRowName.append("图书价格");
    tableRowName.append("入馆日期");
    tableRowName.append("图书数量");
    tableRowName.append("每本书对应的图书编号");

    QStringList tableColumnName;
    tableColumnName.append("名字");
    tableColumnName.append("对应值");
    tableColumnName.append("注意事项");

    this->typeBox = new QComboBox();
    QList<BookCateGory*> bookCateGoryList = SYSTYPE->getAllBookCateGory();

    for (int i = 0; i < bookCateGoryList.size(); ++i)
    {
        typeBox->addItem(bookCateGoryList.at(i)->getCateGoryName(),
                            bookCateGoryList.at(i)->getCateGoryId());
    }

    this->mainTable->setRowCount(tableRowName.size());
    this->mainTable->setColumnCount(tableColumnName.size());
    this->mainTable->setHorizontalHeaderLabels(tableColumnName);

    for (int i = 0; i < tableRowName.size(); ++i)
    {
        this->mainTable->setItem(i, 0, new QTableWidgetItem(tableRowName.at(i)));
        this->mainTable->setItem(i, 1, new QTableWidgetItem());
        if (i != 4 && i != 7)
            this->mainTable->setItem(i, 2, new QTableWidgetItem("*必填"));
        else if(i == 7)
            this->mainTable->setItem(i, 2, new QTableWidgetItem("每本图书编号之间以逗号隔开！"));
    }

    QDate current = QDate::currentDate();
    QString dateIn = current.toString("yyyy-MM-dd");
    this->mainTable->setCellWidget(3, 1, this->typeBox);
    this->mainTable->setItem(5, 1, new QTableWidgetItem(dateIn));
}

QVector<QString> NewBookUI::getBookInfo() const
{
    QVector<QString> bookInfoVec;
    for (int i = 0; i < this->mainTable->rowCount(); ++i)
    {
        if (i != 3)
        {
            QString temp = this->mainTable->item(i, 1)->text();
            bookInfoVec.append(temp);
        }
        else
        {
            QString type = this->typeBox->itemData(this->typeBox->currentIndex(), Qt::UserRole).toString();
            bookInfoVec.append(type);
        }
    }
    return bookInfoVec;
}
