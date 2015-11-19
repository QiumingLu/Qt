#ifndef BOOKGROUPBOX_H
#define BOOKGROUPBOX_H

#include <QWidget>

class QLabel;
class QGroupBox;
class QGridLayout;
class QPushButton;
class UILendBook;
class BookGroupBox : public QWidget
{
    Q_OBJECT

public:
    BookGroupBox(QWidget *parent = 0);
    ~BookGroupBox();

    UILendBook* getLendBook() const;

public:
    QLabel *bookName;
    QLabel *bookCode;
    QLabel *author;
    QLabel *publishing;
    QLabel *category;
    QLabel *price;
    QLabel *dateIn;
    QLabel *quantity_In;
    QLabel *quantity_Out;
    QLabel *quantity;
    QLabel *isBorrow;
    QPushButton *m_lendBook;

private:
    void initUI();
    void createConnections();

private:
    QGroupBox *bookBox;
    QGridLayout* bookLayout;

    QLabel *m_bookName;
    QLabel *m_bookCode;
    QLabel *m_author;
    QLabel *m_publishing;
    QLabel *m_category;
    QLabel *m_price;
    QLabel *m_dateIn;
    QLabel *m_quantity_In;
    QLabel *m_quantity_Out;
    QLabel *m_quantity;
    QLabel *m_isBorrow;

    QPushButton *m_lookDetail;

    UILendBook *lendBook;

signals:
    void signalSelect(QString);

private slots:
    void slotBorrow();
};

#endif // BOOKGROUPBOX_H
