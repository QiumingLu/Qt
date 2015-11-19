#include "booktypelistview.h"
#include <QLabel>
#include <QPushButton>
#include "model/uniquebook.h"
#include "model/books.h"
#include "model/bookcategory.h"
#include "ui/bookgroupbox.h"
#include "core/systype.h"
#include "core/sysinclude.h"

BookTypeListView::BookTypeListView(QWidget *parent) :
    BookListView(parent)
{
}

BookTypeListView::~BookTypeListView()
{
    SAFE_DELETE(bookGroupBox);
}

void BookTypeListView::setUniqueBookList(const QList<UniqueBook *> &uniqueBookList)
{
    this->uniqueBookList = uniqueBookList;
    this->m_BookBoxList.clear();
}

void BookTypeListView::initBookBoxList()
{
    for (int i = 0; i < uniqueBookList.size(); ++i)
    {
        this->uniqueBook = uniqueBookList.at(i);
        this->book = SYSTYPE->getBook(uniqueBook->getBookId());
        this->cateGory = SYSTYPE->getBookCateGrory(book->getCateGoryId());
        this->bookGroupBox = new BookGroupBox(this);
        bookGroupBox->bookName->setText(book->getBookName());
        bookGroupBox->bookCode->setText(uniqueBook->getBookCode());
        bookGroupBox->author->setText(book->getAuthor());
        bookGroupBox->publishing->setText(book->getPublishing());
        bookGroupBox->category->setText(cateGory->getCateGoryName());
        bookGroupBox->price->setText(book->getPrice());
        bookGroupBox->dateIn->setText(book->getdateIN().toString());
        bookGroupBox->quantity_In->setText(QString::number(book->getQuantityIn()));
        bookGroupBox->quantity_Out->setText(QString::number(book->getQuantityOut()));
        bookGroupBox->quantity->setText(QString::number(book->getQuantity()));
        if (uniqueBook->getIsBorrow() == sysinclude::noBorrow) {
            bookGroupBox->isBorrow->text().clear();
            bookGroupBox->isBorrow->setText("是");

        } else {
            bookGroupBox->isBorrow->text().clear();
            bookGroupBox->isBorrow->setText("否");
            bookGroupBox->m_lendBook->setDisabled(true);
        }

        bookGroupBox->move(0, (i*(sysinclude::HEIGHT) + (i+1)*(sysinclude::GRAP)));
        this->m_BookBoxList.append(bookGroupBox);
    }
}

void BookTypeListView::reSizeSlot(int row, int column)
{
    int x = 0, y = 0;
    int n = 0;
    for (int i = 0; i < row; ++i)
    {
        y = i*((sysinclude::HEIGHT)+(sysinclude::GRAP)) + 2*(sysinclude::GRAP);
        for (int j = 0; j < column; ++j)
        {
            x = j*((sysinclude::WIDTH)+(sysinclude::GRAP)) + 2*(sysinclude::GRAP);

            if (n >= m_BookBoxList.size() )
                break;
            this->m_BookBoxList[n++]->move(x, y);
        }
    }
}

int BookTypeListView::getBookSize() const
{
    return this->m_BookBoxList.size();
}
