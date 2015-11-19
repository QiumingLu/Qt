#ifndef UIBOOKINFORMATIONMANAGE_H
#define UIBOOKINFORMATIONMANAGE_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QTableWidget;
class QLineEdit;
class UniqueBook;
class BookUI;
class UIBookInformationManage : public QWidget
{
    Q_OBJECT

public:
    UIBookInformationManage(QWidget *parent = 0);
    ~UIBookInformationManage();

    void initEditOldBook();
    void initBookTable(int bookType);

private:
    void initUI();
    void createConnections();

private:
    QLineEdit *findBook;
    QPushButton *findAction;
    QHBoxLayout *findBtn;
    QTableWidget *bookTable;
    QPushButton *deleteBtn;
    QPushButton *saveBtn;
    QPushButton *closeBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

private:
    QVector<UniqueBook*> uniqueBookVec;
    BookUI *bookUI;

private slots:
    void slotFindBook();
    void slotEdit();
    void slotDetail();
    void slotDelete();
    void slotSave();
};

#endif // UIBOOKINFORMATIONMANAGE_H
