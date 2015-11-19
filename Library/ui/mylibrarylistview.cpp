#include "mylibrarylistview.h"
#include <QLabel>
#include <QPushButton>
#include "core/sysinclude.h"
#include "model/books.h"
#include "model/uniquebook.h"
#include "model/bookcategory.h"
#include "ui/mylibrarybox.h"
#include "core/systype.h"
#include "model/sysenviroment.h"
#include "model/readers.h"
#include "model/borrow.h"


MyLibraryListView::MyLibraryListView(QWidget *parent) :
    BookListView(parent)
{
}

MyLibraryListView::~MyLibraryListView()
{
    SAFE_DELETE(myLibraryBox);
}

void MyLibraryListView::initBookBoxList()
{
    int readerId = SysEnviroment::getInstance()->getReader()->getReaderId();
    this->readerBorrowVec = SYSTYPE->getReaderBorrow(readerId);
    for(int i = 0; i < readerBorrowVec.size(); ++i)
    {
        int uniqueBookId = readerBorrowVec.at(i)->getBookId();
        this->uniqueBook = SYSTYPE->getUniqueBook(uniqueBookId);
        this->book = SYSTYPE->getBook(uniqueBook->getBookId());
        this->bookCategory = SYSTYPE->getBookCateGrory(book->getCateGoryId());

        this->myLibraryBox = new MyLibraryBox(this);
        myLibraryBox->bookName->setText(book->getBookName());
        myLibraryBox->bookCode->setText(uniqueBook->getBookCode());
        myLibraryBox->author->setText(book->getAuthor());
        myLibraryBox->publishing->setText(book->getPublishing());
        myLibraryBox->category->setText(bookCategory->getCateGoryName());
        myLibraryBox->price->setText(book->getPrice());
        myLibraryBox->dateIn->setText(book->getdateIN().toString());
        myLibraryBox->dateBorrow->setText(readerBorrowVec.at(i)->getDateBorrow().toString());
        myLibraryBox->dateReturn->setText(readerBorrowVec.at(i)->getDateReturn().toString());
        if (readerBorrowVec.at(i)->isLoss() == 1) {
            myLibraryBox->isloss->setText("是");
            myLibraryBox->m_returnBook->setDisabled(true);
            myLibraryBox->m_loss->setText("取消挂失");

        } else {
            myLibraryBox->isloss->setText("否");
            myLibraryBox->m_returnBook->setDisabled(false);
            myLibraryBox->m_loss->setText("挂失");
        }

        myLibraryBox->move(0, (i*(sysinclude::HEIGHT) + (i+1)*(sysinclude::GRAP)));
        this->m_LibraryBoxList.append(myLibraryBox);
    }
}

void MyLibraryListView::reSizeSlot(int row, int column)
{
    int x = 0, y = 0;
    int n = 0;
    for (int i = 0; i < row; ++i)
    {
        y = i*((sysinclude::HEIGHT)+(sysinclude::GRAP)) + 2*(sysinclude::GRAP);
        for (int j = 0; j < column; ++j)
        {
            x = j*((sysinclude::WIDTH)+(sysinclude::GRAP)) + 2*(sysinclude::GRAP);

            if (n >= this->m_LibraryBoxList.size()) {
                break;
            }
            this->m_LibraryBoxList[n++]->move(x, y);
        }
    }
}

int MyLibraryListView::getBookSize() const
{
    return this->m_LibraryBoxList.size();
}
