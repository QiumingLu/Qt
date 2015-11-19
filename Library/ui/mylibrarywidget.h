#ifndef MYLIBRARYWIDGET_H
#define MYLIBRARYWIDGET_H

#include <QWidget>
#include "ui/customdialog.h"

class QScrollBar;
class BookListWidget;
class QHBoxLayout;
class UniqueBook;
class MyLibraryWidget : public QWidget
{
    Q_OBJECT

public:
    MyLibraryWidget(QWidget *parent = 0, int type = 0);
    ~MyLibraryWidget();

    void initBookListWidget(int type);
    BookListWidget* getBookListWidget() const;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initUI();
    void createConnections();

private:
    BookListWidget* m_BookListWidget;
    QScrollBar* m_VScrollBar;
    QHBoxLayout* mainLayout;
    int type;

private slots:
    void displayListView(int);

signals:
    void SendReSizeSignal(int, int);
};

#endif // MYLIBRARYWIDGET_H
