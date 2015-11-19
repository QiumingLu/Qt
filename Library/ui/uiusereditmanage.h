#ifndef UIUSEREDITMANAGE_H
#define UIUSEREDITMANAGE_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QTableWidget;
class Readers;
class UIRegister;
class UIUserEditManage : public QWidget
{
    Q_OBJECT

public:
    UIUserEditManage(QWidget *parent = 0);
    ~UIUserEditManage();
    void initReaderTable();

private:
    void initUI();
    void createConnections();

private:
    QTableWidget *readerTable;
    QPushButton *deleteBtn;
    QPushButton *addBtn;
    QPushButton *closeBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *mainLayout;

    UIRegister *uiRegister;
    QList<Readers*> readerList;

private slots:
    void slotDelete();
    void slotShowRegister();
    void slotRegister();
    void slotEdit();
    void slotDetail();
};

#endif // UIUSEREDITMANAGE_H
