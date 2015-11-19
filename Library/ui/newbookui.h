#ifndef NEWBOOKUI_H
#define NEWBOOKUI_H

#include <QWidget>
#include <QVector>

class QTableWidget;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QTextEdit;
class QLabel;
class QComboBox;
class NewBookUI : public QWidget
{
public:
    NewBookUI(QWidget *parent = 0);
    ~NewBookUI();

    QVector<QString> getBookInfo() const;

private:
    void initUI();
    void initTable();

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
    QVBoxLayout *mainLayout;
    QComboBox *typeBox;
};

#endif // NEWBOOKUI_H
