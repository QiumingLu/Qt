#include "books.h"

Books::Books()
{
}

Books::~Books()
{
}

int Books::getBookId() const
{
    return this->bookId;
}

void Books::setBookId(int bookId)
{
    this->bookId = bookId;
}

QString Books::getBookName() const
{
    return this->bookName;
}

void Books::setBookName(const QString &bookName)
{
    this->bookName = bookName;
}

QString Books::getAuthor() const
{
    return this->author;
}

void Books::setAuthor(const QString &author)
{
    this->author = author;
}

QString Books::getPublishing() const
{
    return this->publishing;
}

void Books::setPublishing(const QString &publishing)
{
    this->publishing = publishing;
}

int Books::getCateGoryId() const
{
    return this->categoryId;
}

void Books::setCateGoryId(int categoryId)
{
    this->categoryId = categoryId;
}

QString Books::getPrice() const
{
    return this->price;
}

void Books::setPrice(const QString &price)
{
    this->price = price;
}

QDate Books::getdateIN() const
{
    return this->dateIN;
}

void Books::setdateIN(const QDate &dateIN)
{
    this->dateIN = dateIN;
}

int Books::getQuantityIn() const
{
    return this->quantityIn;
}

void Books::setQuantityIn(int quantityIn)
{
    this->quantityIn = quantityIn;
}

int Books::getQuantityOut() const
{
    return this->quantityOut;
}

void Books::setQuantityOut(int quantityOut)
{
    this->quantityOut = quantityOut;
}

int Books::getQuantity() const
{
    return this->quantity;
}

void Books::setQuantity(int quantity)
{
    this->quantity = quantity;
}

