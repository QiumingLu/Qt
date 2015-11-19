#ifndef UIUSERCENTER_H
#define UIUSERCENTER_H

#include <QMainWindow>

class QLabel;
class QGroupBox;
class QGridLayout;
class QSplitter;
class QPushButton;
class QHBoxLayout;
class QComboBox;
class MyInfoWidget;
class MyLibraryWidget;
class IconedLineEdit;
class Books;
class BookCateGory;
class UniqueBook;
class UIUserCenter : public QMainWindow
{
    Q_OBJECT

public:
    UIUserCenter(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~UIUserCenter();

private:
    void initUi();
    void createConnections();

private:
    QLabel *banner;
    QGridLayout *mainLayout;
    QGroupBox *mainBox;
    QSplitter *mainSplitter;
    QWidget *mainWidget;
    IconedLineEdit *m_findBook;
    QPushButton *findBook;
    QPushButton *myInfomation;
    QPushButton *myLibrary;
    QPushButton *refleshBtn;
    QComboBox *bookCateGory;
    QHBoxLayout *btnLayout;
    QWidget *btnWidget;
    MyInfoWidget *myInfoWidget;
    MyLibraryWidget *myLibraryWidget;

    QList<MyLibraryWidget*> bookTypeWidget;
    QList<BookCateGory*> bookCateGoryList;
    QVector<UniqueBook*> bookVect;
    QList<UniqueBook*> bookList;

    bool infoflags;
    bool ifInputBook;

private slots:
    void slotMyInfoShow();
    void slotMyLibraryShow();
    void slotShowBook(int bookType);
    void slotFindBook();
    void slotReflesh();
};

#endif // UIUSERCENTER_H
