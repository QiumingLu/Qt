#ifndef MYLIBRARYBOX_H
#define MYLIBRARYBOX_H

#include <QWidget>

class QGroupBox;
class QGridLayout;
class QVBoxLayout;
class QLabel;
class QPushButton;
class MyLibraryBox : public QWidget
{
    Q_OBJECT

public:
    MyLibraryBox(QWidget *parent = 0);
    ~MyLibraryBox();

private:
    void initUI();
    void createConnections();

public:
    QLabel *bookName;
    QLabel *bookCode;
    QLabel *author;
    QLabel *publishing;
    QLabel *category;
    QLabel *price;
    QLabel *dateIn;
    QLabel *dateBorrow;
    QLabel *dateReturn;
    QLabel *isloss;
    QPushButton *m_loss;
    QPushButton *m_returnBook;

private:
    QGridLayout* borrowLayout;
    QGroupBox* borrowBox;

    QLabel *m_bookName;
    QLabel *m_bookCode;
    QLabel *m_author;
    QLabel *m_publishing;
    QLabel *m_category;
    QLabel *m_price;
    QLabel *m_dateIn;
    QLabel *m_dateBorrow;
    QLabel *m_dateReturn;
    QLabel *m_isloss;

private slots:
    void slotLoss();
    void slotReturn();
};

#endif // MYLIBRARYBOX_H
