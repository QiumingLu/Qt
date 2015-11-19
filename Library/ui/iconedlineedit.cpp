#include "iconedlineedit.h"
#include <QLabel>
#include <QIcon>
#include <QHBoxLayout>

IconedLineEdit::IconedLineEdit(QWidget *parent)
    :QLineEdit(parent)
{
    int size = this->height()*0.65;
    this->label = new QLabel();
    this->label->setFixedSize(size, size);
    this->label->setObjectName("label");
    this->label->setFocusPolicy(Qt::NoFocus);           //得到焦点时，不显示虚线框
    this->label->setStyleSheet("border-style: none");   //消除边框

    this->labelLayout = new QHBoxLayout();
    this->labelLayout->setContentsMargins(6, 0, 6, 0);
    this->labelLayout->addWidget(this->label);
    this->labelLayout->addStretch();
    this->setLayout(this->labelLayout);
    setTextMargins(size + 2, 1, 0, 1);    //设置输入框中文件输入区，不让输入的文字在被隐藏在按钮下
}

IconedLineEdit::~IconedLineEdit()
{
    delete label;
    delete labelLayout;
}

void IconedLineEdit::setIcon(const QIcon &icon)
{
    label->setPixmap(icon.pixmap(label->size()));
}
