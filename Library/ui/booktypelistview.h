#ifndef BOOKTYPELISTVIEW_H
#define BOOKTYPELISTVIEW_H

#include "ui/booklistview.h"

class BookGroupBox;
class BookCateGory;
class Books;
class UniqueBook;
class BookTypeListView : public BookListView
{
    Q_OBJECT

public:
    BookTypeListView(QWidget *parent = 0);
    ~BookTypeListView();

    void initBookBoxList();
    int getBookSize() const;

    void setUniqueBookList(const QList<UniqueBook*> &uniqueBookList);

private:
    UniqueBook* uniqueBook;
    Books* book;
    BookCateGory *cateGory;
    BookGroupBox* bookGroupBox;
    QList<BookGroupBox*> m_BookBoxList;
    QList<UniqueBook*> uniqueBookList;

public slots:
    void reSizeSlot(int row, int column);
};

#endif // BOOKTYPELISTVIEW_H
