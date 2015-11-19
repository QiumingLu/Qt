/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef BOOKS_H
#define BOOKS_H

#include <QObject>
#include <QDate>

class Books : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int BOOK_ID READ getBookId WRITE setBookId)
    Q_PROPERTY(QString BOOK_NAME READ getBookName WRITE setBookName)
    Q_PROPERTY(QString AUTHOR READ getAuthor WRITE setAuthor)
    Q_PROPERTY(QString PUBLISHING READ getPublishing WRITE setPublishing)
    Q_PROPERTY(int CATEGORY_ID READ getCateGoryId WRITE setCateGoryId)
    Q_PROPERTY(QString PRICE READ getPrice WRITE setPrice)
    Q_PROPERTY(QDate DATE_IN READ getdateIN WRITE setdateIN)
    Q_PROPERTY(int QUANTITY_IN READ getQuantityIn WRITE setQuantityIn)
    Q_PROPERTY(int QUANTITY_OUT READ getQuantityOut WRITE setQuantityOut)
    Q_PROPERTY(int QUANTITY READ getQuantity WRITE setQuantity)

public:
    Books();
    ~Books();

    int getBookId() const;
    void setBookId(int);

    QString getBookName() const;
    void setBookName(const QString &);

    QString getAuthor() const;
    void setAuthor(const QString &);

    QString getPublishing() const;
    void setPublishing(const QString &);

    int getCateGoryId() const;
    void setCateGoryId(int);

    QString getPrice() const;
    void setPrice(const QString &);

    QDate getdateIN() const;
    void setdateIN(const QDate &);

    int getQuantityIn() const;
    void setQuantityIn(int);

    int getQuantityOut() const;
    void setQuantityOut(int);

    int getQuantity() const;
    void setQuantity(int);

private:
    int bookId;
    QString bookName;
    QString author;
    QString publishing;
    int categoryId;
    QString price;
    QDate dateIN;
    int quantityIn;
    int quantityOut;
    int quantity;
};

#endif // BOOKS_H
