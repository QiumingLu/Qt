#ifndef UIBOOKTABLEBASE_H
#define UIBOOKTABLEBASE_H

#include <QWidget>
#include <QList>
#include <QModelIndex>

class QStandardItemModel;
class QTableView;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QItemSelectionModel;
class UIBookTableBase : public QWidget
{
    Q_OBJECT

public:
    explicit UIBookTableBase(QString assembly, QWidget *parent = 0);
    virtual ~UIBookTableBase();

    void initBookTableBase();
    bool isSaved();

public:
    QPushButton *insertBtn;
    QHBoxLayout *buttomLayout;
    QGridLayout *rightGridLayout;

protected:
    void setUpModel() {}
    void setUpView();
    void createConnections();
    void addModifyData(int mid);

protected:
    QString assembly;
    QString tableviewDataChange;
    QStandardItemModel *model;
    QModelIndex index;
    QItemSelectionModel *selectionModel;

    QTableView *outputTable;
    QPushButton *saveModelBtn;
    QPushButton *deleteModelBtn;

    QList<int> deleteData;       //被删除的数据id
    QList<int> modifiedData;     //被修改的数据对应的dataList的位置

private:
    QVBoxLayout *rightLayout;
    int currentID;

signals:
    void signalIfChanged(bool);

public slots:
    void slotDeleteRow();
    void slotItemPress(QModelIndex);

    virtual void indexClicked(QModelIndex){}
    virtual void insertList(QModelIndex parent, int start, int end) {}
    virtual void deleteList(QModelIndex parent, int start, int end) {}
    virtual void dataChanged(QModelIndex topLeft, QModelIndex bottomRight) {}
    virtual void slotSave() {}
    virtual void slotInsertRow() {}

    /*保存修改前的信息， 用于合法性判读后恢复原值*/
    void slotSaveChangedData(QModelIndex);
};

#endif // UIBOOKTABLEBASE_H
