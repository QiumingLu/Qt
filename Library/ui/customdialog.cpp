#include "customdialog.h"
#include "ui/titlebar.h"
#include <QVBoxLayout>

CustomDialog::CustomDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint);
    this->m_titleBar = new TitleBar();
    this->m_titleBar->setMaximizeVisible(false);
    this->m_dialog = new QDialog();

    this->vbox = new QVBoxLayout(this);
    this->vbox->setContentsMargins(0, 0, 0, 0);
    this->vbox->addWidget(m_titleBar);
    this->vbox->setSpacing(0);
    this->vbox->addWidget(m_dialog);

    QDialog::setLayout(this->vbox);

    QObject::connect(this->m_titleBar, SIGNAL(closed()), this, SLOT(close()));
    QObject::connect(this->m_titleBar, SIGNAL(minimized()), this, SLOT(showMinimized()));
    QObject::connect(this->m_titleBar, SIGNAL(maxRestored()), this, SLOT(switchMaxNormal()));
    QObject::connect(this->m_titleBar, SIGNAL(moved(QPoint)), this, SLOT(moveBy(QPoint)));
}

CustomDialog::~CustomDialog()
{

}

void CustomDialog::setWindowIcon(const QIcon &pix)
{
    this->m_titleBar->setWindowIcon(pix);
    QWidget::setWindowIcon(pix);
}

TitleBar* CustomDialog::titleBar() const
{
    return this->m_titleBar;
}

void CustomDialog::setLayout(QLayout *layout)
{
    this->m_dialog->setLayout(layout);
}

void CustomDialog::showMaximized()
{
    this->m_titleBar->showMaxRestore(true);
    QWidget::showMaximized();
}

void CustomDialog::showNormal()
{
    this->m_titleBar->showMaxRestore(false);
    QWidget::showNormal();
}

void CustomDialog::switchMaxNormal()
{
    if (windowState() == Qt::WindowMaximized)
    {
        this->showNormal();
    } else {
        this->showMaximized();
    }
}

void CustomDialog::setWindowTitle(const QString &title)
{
    this->m_titleBar->setWindowTitle(title);
    QWidget::setWindowTitle(title);
}

void CustomDialog::moveBy(const QPoint &delta)
{
    this->move(delta);
}

void CustomDialog::setWindowModified(bool mod)
{
    this->m_titleBar->setWindowModified(mod);
    QWidget::setWindowModified(mod);
}

