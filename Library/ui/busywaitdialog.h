#ifndef BUSYWAITDIALOG_H
#define BUSYWAITDIALOG_H

#include <QDialog>
#include <QFutureWatcher>

class QLabel;
class QMovie;
class BusyWaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BusyWaitDialog(QWidget *p4arent = 0);
    ~BusyWaitDialog();

    void setMessage(const QString &msg);
private:
    QLabel *msgLabel;
    QLabel *movieLable;
    QMovie *movie;
    void initUI();
};

#endif // BUSYWAITDIALOG_H
