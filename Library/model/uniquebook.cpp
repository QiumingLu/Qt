#include "uniquebook.h"

UniqueBook* UniqueBook::uniqueBook = NULL;

UniqueBook::UniqueBook()
{
}

UniqueBook::~UniqueBook()
{

}

int UniqueBook::getId() const
{
    return this->id;
}

void UniqueBook::setId(int id)
{
    this->id = id;
}

QString UniqueBook::getBookCode() const
{
    return this->bookCode;
}

void UniqueBook::setBookCode(const QString &bookCode)
{
    this->bookCode = bookCode;
}

int UniqueBook::getBookId() const
{
    return this->bookId;
}

void UniqueBook::setBookId(int bookId)
{
    this->bookId = bookId;
}

int UniqueBook::getIsBorrow() const
{
    return this->isBorrow;
}

void UniqueBook::setIsBorrow(int isBorrow)
{
    this->isBorrow = isBorrow;
}

QDate UniqueBook::getLassBorrow() const
{
    return this->lassBorrow;
}

void UniqueBook::setLassBorrow(const QDate &lassBorrow)
{
    this->lassBorrow = lassBorrow;
}

QDate UniqueBook::getLassReturn() const
{
    return this->lassReturn;
}

void UniqueBook::setLassReturn(const QDate &lassReturn)
{
    this->lassReturn = lassReturn;
}

QList<UniqueBook*> UniqueBook::getBookList() const
{
    return this->uniqueBookList;
}

void UniqueBook::setBookList(const QList<UniqueBook *> &uniqueBookList)
{
    this->uniqueBookList = uniqueBookList;
}
