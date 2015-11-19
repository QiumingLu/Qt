#ifndef ADDBOOKCATEGORY_H
#define ADDBOOKCATEGORY_H

#include <QWidget>
#include "ui/addbasewidget.h"

class BookCateGory;
class AddBookCateGory : public AddBaseWidget
{
    Q_OBJECT

public:
   explicit AddBookCateGory(QWidget *parent = 0);
    ~AddBookCateGory();

private:
    void initTable();
    QVector<QString> getTableText() const;

private:
    BookCateGory *bookCateGory;

private slots:
    void slotSave();
};

#endif // ADDBOOKCATEGORY_H
