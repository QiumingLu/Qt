#include "borrow.h"

Borrow::Borrow()
{
}

Borrow::~Borrow()
{
}

int Borrow::getBorrowId() const
{
    return this->borrowId;
}

void Borrow::setBorrowId(int borrowId)
{
    this->borrowId = borrowId;
}

int Borrow::getReaderId() const
{
    return this->readerId;
}

void Borrow::setReaderId(int readerId)
{
    this->readerId = readerId;
}

int Borrow::getBookId() const
{
    return this->bookId;
}

void Borrow::setBookId(int bookId)
{
    this->bookId = bookId;
}

QDate Borrow::getDateBorrow() const
{
    return this->dateBorrow;
}

void Borrow::setDateBorrow(const QDate &dateBorrow)
{
    this->dateBorrow = dateBorrow;
}

QDate Borrow::getDateReturn() const
{
    return this->dateReturn;
}

void Borrow::setDateReturn(const QDate &dateReturn)
{
    this->dateReturn = dateReturn;
}

int Borrow::isLoss() const
{
    return this->loss;
}

void Borrow::setLoss(int loss)
{
    this->loss = loss;
}
