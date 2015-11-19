/*
 * @Author: QiumingLu
 * @Date: 2014.11.22
 */
#ifndef BOOKCATEGORY_H
#define BOOKCATEGORY_H

#include <QObject>

class BookCateGory : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int  CATEGORY_ID READ getCateGoryId WRITE setCateGoryId)
    Q_PROPERTY(QString CATEGORY_NAME READ getCateGoryName WRITE setCateGoryName)

public:
    BookCateGory();
    ~BookCateGory();

    int getCateGoryId() const;
    void setCateGoryId(int);

    QString getCateGoryName() const;
    void setCateGoryName(const QString &);

private:
    int categoryId;
    QString categoryName;
};

#endif // BOOKCATEGORY_H
