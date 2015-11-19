#include "readers.h"

Readers::Readers()
{
}

Readers::~Readers()
{
}

int Readers::getId() const
{
    return this->id;
}

void Readers::setId(int id)
{
    this->id = id;
}

int Readers::getReaderId() const
{
    return this->readerId;
}

void Readers::setReaderId(int readerId)
{
    this->readerId = readerId;
}

QString Readers::getCardName() const
{
    return this->cardName;
}

void Readers::setCardName(const QString &cardName)
{
    this->cardName = cardName;
}

QString Readers::getCardId() const
{
    return this->cardId;
}

void Readers::setCardId(const QString &cardId)
{
    this->cardId = cardId;
}

int Readers::getCardLevel() const
{
    return this->cardLevel;
}

void Readers::setCardLevel(int cardLevel)
{
    this->cardLevel = cardLevel;
}

QDate Readers::getDay() const
{
    return this->day;
}

void Readers::setDay(const QDate &day)
{
    this->day = day;
}
