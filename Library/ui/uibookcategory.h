#ifndef UIBOOKCATEGORY_H
#define UIBOOKCATEGORY_H

#include <QWidget>

class QPushButton;
class QTableWidget;
class QHBoxLayout;
class QVBoxLayout;
class BookCateGory;
class AddBookCateGory;
class UIBookCateGory : public QWidget
{
    Q_OBJECT

public:
    UIBookCateGory(QWidget *parent = 0);
    ~UIBookCateGory();

    void initTable();

private:
    void initUI();
    void createConnections();

private:
    QTableWidget *bookCateGoryTable;
    QPushButton *deleteBtn;
    QPushButton *addBtn;
    QPushButton *closeBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private:
    QList<BookCateGory*> bookCateGoryList;
    AddBookCateGory *addCateGory;

private slots:
    void slotAdd();
};

#endif // UIBOOKCATEGORY_H
