#ifndef UNIQUEBOOK_H
#define UNIQUEBOOK_H

#include <QObject>
#include <QDate>

class UniqueBook : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int ID READ getId WRITE setId)
    Q_PROPERTY(QString BOOK_CODE READ getBookCode WRITE setBookCode)
    Q_PROPERTY(int BOOK_ID READ getBookId WRITE setBookId)
    Q_PROPERTY(int ISBORROW READ getIsBorrow WRITE setIsBorrow)
    Q_PROPERTY(QDate LASSBORROW READ getLassBorrow WRITE setLassBorrow)
    Q_PROPERTY(QDate LASSRETURN READ getLassReturn WRITE setLassReturn)

public:
    UniqueBook();
    ~UniqueBook();

    int getId() const;
    void setId(int);

    QString getBookCode() const;
    void setBookCode(const QString &);

    int getBookId() const;
    void setBookId(int);

    int getIsBorrow() const;
    void setIsBorrow(int);

    QDate getLassBorrow() const;
    void setLassBorrow(const QDate &);

    QDate getLassReturn() const;
    void setLassReturn(const QDate &);

    void setBookList(const QList<UniqueBook *> &);
    QList<UniqueBook*> getBookList() const;

    static UniqueBook* getInstance() {
        if (uniqueBook == NULL)
        {
            uniqueBook = new UniqueBook();
        }
        return uniqueBook;
    }

private:
    int id;
    QString bookCode;
    int bookId;
    int isBorrow;
    QDate lassBorrow;
    QDate lassReturn;

    QList<UniqueBook*> uniqueBookList;
    static UniqueBook* uniqueBook;
};

#endif // UNIQUEBOOK_H
