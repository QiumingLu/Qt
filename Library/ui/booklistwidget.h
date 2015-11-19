#ifndef BOOKLISTWIDGET_H
#define BOOKLISTWIDGET_H

#include <QWidget>

class BookListView;
class QGridLayout;
class BookListWidget : public QWidget
{
    Q_OBJECT

public:
    BookListWidget(QWidget *parent = 0, int type = 0);
    ~BookListWidget();

public:
    BookListView* getBookListView() const;

private:
    void initUI();
    BookListView *m_bookListView;
    QGridLayout *mainLayout;
    int type;
};

#endif // BOOKLISTWIDGET_H
