/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef READERS_H
#define READERS_H

#include <QObject>
#include <QDate>
#include "user.h"

class Readers : public User
{
    Q_OBJECT

    Q_PROPERTY(int ID READ getId WRITE setId)
    Q_PROPERTY(int READER_ID READ getReaderId WRITE setReaderId)
    Q_PROPERTY(QString CARD_NAME READ getCardName WRITE setCardName)
    Q_PROPERTY(QString CARD_ID READ getCardId WRITE setCardId)
    Q_PROPERTY(int CARD_LEVEL READ getCardLevel WRITE setCardLevel)
    Q_PROPERTY(QDate DAY READ getDay WRITE setDay)

public:
    Readers();
    ~Readers();

    int getId() const;
    void setId(int);

    int getReaderId() const;
    void setReaderId(int);

    QString getCardName() const;
    void setCardName(const QString &);

    QString getCardId() const;
    void setCardId(const QString &);

    int getCardLevel() const;
    void setCardLevel(int);

    QDate getDay() const;
    void setDay(const QDate &);

private:
    int id;
    int readerId;
    QString cardName;
    QString cardId;
    int cardLevel;
    QDate day;
};

#endif // READERS_H
