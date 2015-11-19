#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>

class TitleBar;
class QVBoxLayout;
class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = 0);
    virtual ~CustomDialog();

    void setWindowIcon(const QIcon &pix);
    void setLayout(QLayout *layout);
    TitleBar *titleBar() const;

public slots:
    void showMaximized();
    void showNormal();
    void switchMaxNormal();
    void setWindowTitle(const QString &title);
    void moveBy(const QPoint &delta);
    void setWindowModified(bool mod);

private:
    TitleBar *m_titleBar;
    QWidget *m_dialog;
    QVBoxLayout *vbox;
};

#endif // CUSTOMDIALOG_H
