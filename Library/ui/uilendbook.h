#ifndef UILENDBOOK_H
#define UILENDBOOK_H

#include <QWidget>

class Readers;
class QDateEdit;
class QLabel;
class QGridLayout;
class QPushButton;
class UILendBook : public QWidget
{
    Q_OBJECT

public:
    UILendBook(QWidget *parent = 0);
    ~UILendBook();

private:
    void initUI();
    void createConnections();

private:
    QLabel *m_level;
    QLabel *m_day;
    QLabel *m_lendBooks;
    QLabel *m_lendBookNum;
    QLabel *m_lendTime;
    QLabel *m_returnTime;

    QLabel *level;
    QLabel *day;
    QLabel *lendBooks;
    QLabel *lendBookNum;
    QLabel *lendTime;
    QDateEdit *returnTime;

    QGridLayout *mainLayout;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    Readers *reader;
    QString bookCode;

private slots:
    void slotLendBook();

public slots:
    void slotSelectBook(QString);
};

#endif // UILENDBOOK_H
