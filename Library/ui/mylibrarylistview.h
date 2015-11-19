#ifndef MYLIBRARYLISTVIEW_H
#define MYLIBRARYLISTVIEW_H

#include "ui/booklistview.h"

class UniqueBook;
class Books;
class BookCateGory;
class Borrow;
class MyLibraryBox;
class MyLibraryListView : public BookListView
{
    Q_OBJECT

public:
    MyLibraryListView(QWidget *parent = 0);
    ~MyLibraryListView();

    void initBookBoxList();
    int getBookSize() const;

private:
    UniqueBook *uniqueBook;
    Books *book;
    BookCateGory *bookCategory;
    MyLibraryBox* myLibraryBox;
    QList<MyLibraryBox*> m_LibraryBoxList;
    QVector<Borrow*> readerBorrowVec;

public slots:
    void reSizeSlot(int row, int column);
};

#endif // MYLIBRARYLISTVIEW_H
