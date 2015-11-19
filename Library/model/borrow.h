/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef BORROW_H
#define BORROW_H

#include <QObject>
#include <QDate>

class Borrow : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int ID READ getBorrowId WRITE setBorrowId)
    Q_PROPERTY(int READER_ID READ getReaderId WRITE setReaderId)
    Q_PROPERTY(int BOOK_ID READ getBookId WRITE setBookId)
    Q_PROPERTY(QDate DATE_BORROW READ getDateBorrow WRITE setDateBorrow)
    Q_PROPERTY(QDate DATE_RETURN READ getDateReturn WRITE setDateReturn)
    Q_PROPERTY(int LOSS READ isLoss WRITE setLoss)

public:
    Borrow();
    ~Borrow();

    int getBorrowId() const;
    void setBorrowId(int);

    int getReaderId() const;
    void setReaderId(int);

    int getBookId() const;
    void setBookId(int);

    QDate getDateBorrow() const;
    void setDateBorrow(const QDate &);

    QDate getDateReturn() const;
    void setDateReturn(const QDate &);

    int isLoss() const;
    void setLoss(int);

private:
    int borrowId;
    int readerId;
    int bookId;
    QDate dateBorrow;
    QDate dateReturn;
    int loss;
};

#endif // BORROW_H
