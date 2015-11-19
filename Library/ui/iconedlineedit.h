#ifndef ICONEDLINEEDIT_H
#define ICONEDLINEEDIT_H

#include <QLineEdit>

class QLabel;
class QIcon;
class QHBoxLayout;
class IconedLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit IconedLineEdit(QWidget *parent = 0);
    ~IconedLineEdit();

private:
    QLabel *label;
    QHBoxLayout *labelLayout;

public slots:
    void setIcon(const QIcon &icon);
};

#endif // ICONEDLINEEDIT_H
