#ifndef BOOKUI_H
#define BOOKUI_H

#include <QWidget>

class QTableWidget;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QTextEdit;
class QLabel;
class QComboBox;
class UniqueBook;
class BookUI : public QWidget
{
    Q_OBJECT

public:
    BookUI(QWidget *parent = 0);
    ~BookUI();

    bool initTable(UniqueBook *uniqueBook);

private:
    void initUI();
    void createConnections();
    QVector<QString> getBookInfo();

private:
    QTableWidget *mainTable;
    QLabel *m_contentL;
    QLabel *m_authorL;
    QLabel *m_includeL;
    QLabel *m_descrideL;
    QTextEdit *content;
    QTextEdit *author;
    QTextEdit *include;
    QTextEdit *descride;
    QHBoxLayout *topLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *btnLayout;
    QPushButton *confirnBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *mainLayout;

    UniqueBook *uniqueBook;
    QComboBox *typeBox;

private slots:
    void slotSaveEdit();
};

#endif // BOOKUI_H
