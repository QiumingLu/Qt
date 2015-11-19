#include "titlebar.h"
#include <QToolButton>
#include <QPalette>
#include <QPixmap>
#include <QStyle>
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include <QMouseEvent>
#include "core/sysinclude.h"

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),maxNormal(false)
{
    setAutoFillBackground(true);

    QPalette p = palette();
    QLinearGradient gradient(0, 0, 0, 24);
    gradient.setColorAt(0, QColor(Qt::darkGray).lighter());
    gradient.setColorAt(1, Qt::lightGray);
    p.setBrush(QPalette::Background, QBrush(Qt::NoBrush));
    this->setTitleTransparent();
    setPalette(p);

    this->minimize = new QToolButton(this);
    this->maximize = new QToolButton(this);
    this->close = new QToolButton(this);

    QPixmap pix = this->style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    this->close->setIcon(pix);
    this->maxPix = this->style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    pix = this->style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    this->minimize->setIcon(pix);
    this->restorePix = this->style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
    this->maximize->setIcon(restorePix);
    this->minimize->setMinimumHeight(20);
    this->close->setMinimumHeight(20);
    this->maximize->setMinimumHeight(20);

    this->label = new QLabel(this);
    this->label->setText("Window Title");
    this->icon = new QLabel(this);

    this->hbox = new QHBoxLayout(this);
    this->hbox->setContentsMargins(0, 0, 0, 5);
    this->hbox->addWidget(icon);
    this->hbox->addWidget(label);
    this->hbox->addWidget(minimize);
    this->hbox->addWidget(maximize);
    this->hbox->addWidget(close);

    this->hbox->insertStretch(2, 500);
    this->hbox->setSpacing(0);
    this->hbox->insertSpacing(1, 5);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QObject::connect(this->close, SIGNAL(clicked()), this, SIGNAL(closed()));
    QObject::connect(this->minimize, SIGNAL(clicked()), this, SIGNAL(minimized()));
    QObject::connect(this->maximize, SIGNAL(clicked()), this, SIGNAL(maxRestored()));

    this->setWindowIcon(QApplication::windowIcon());
}

TitleBar::~TitleBar()
{
    SAFE_DELETE(minimize);
    SAFE_DELETE(maximize);
    SAFE_DELETE(close);
    SAFE_DELETE(label);
    SAFE_DELETE(icon);
    SAFE_DELETE(hbox);
}

void TitleBar::showMaxRestore(const bool maximized)
{
    this->maxNormal = maximized;
    if (maximized)
    {
        maximize->setIcon(restorePix);
    } else {
        maximize->setIcon(maxPix);
    }
}

void TitleBar::mousePressEvent(QMouseEvent *me)
{
    startPos = me->globalPos();
    clickPos = mapToParent(me->pos());
}

void TitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if (maxNormal)
        return;
    emit moved(me->globalPos() - clickPos);
}

void TitleBar::mouseDoubleClickEvent(QMoveEvent *)
{
    emit maxRestored();
}

void TitleBar::setWindowTitle(const QString &title)
{
    if (title.contains("[*]"))
    {
        QString content = title.left(title.length() - 3);
        if (isWindowModified())
        {
            content.append("*");
            label->setText(content);
        } else {
            label->setText(content);
        }
    } else {
        label->setText(title);
    }
    QWidget::setWindowTitle(title);
}

void TitleBar::setWindowIcon(const QIcon &pix)
{
    icon->setPixmap(pix.pixmap(24, 24));
}

void TitleBar::setWindowModified(bool mod)
{
    QString title = QWidget::windowTitle();
    if (title.contains("[*]"))
    {
        QString content = title.left(title.length() - 3);
        if (mod)
        {
            content.append("*");
            label->setText(content);
        } else {
            label->setText(content);
        }
    } else {
        label->setText(title);
    }
    QWidget::setWindowModified(mod);
}

void TitleBar::setMinimizeVisible(bool visible)
{
    minimize->setVisible(visible);
}

void TitleBar::setMaximizeVisible(bool visible)
{
    maximize->setVisible(visible);
}

void TitleBar::setCloseVisible(bool visible)
{
    close->setVisible(visible);
}

void TitleBar::setTitleTransparent()
{
    QPalette tmp;
    tmp.setBrush(QPalette::Background, QBrush(QColor(0, 0, 0, 0)));
    setPalette(tmp);
}
