#ifndef BOOKLISTVIEW_H
#define BOOKLISTVIEW_H

#include <QListView>

class UniqueBook;
class BookListView : public QListView
{
    Q_OBJECT

public:
    explicit BookListView(QWidget *parent = 0);
    virtual ~BookListView();
    virtual int getBookSize() const = 0;
    virtual void initBookBoxList() = 0;
    virtual void setUniqueBookList(const QList<UniqueBook*> &) {}

public slots:
    virtual void reSizeSlot(int row, int column) = 0;
};

#endif // BOOKLISTVIEW_H
