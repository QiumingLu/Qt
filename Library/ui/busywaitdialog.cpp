#include "busywaitdialog.h"
#include <QLabel>
#include <QMovie>
#include <QDesktopWidget>
#include <QApplication>

BusyWaitDialog::BusyWaitDialog(QWidget *parent) :
    QDialog(parent)
{
    this->initUI();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle(tr("请稍等..."));
    movie = new QMovie(":/");
    movieLable->setMovie(movie);
    movie->start();

    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
}

BusyWaitDialog::~BusyWaitDialog()
{
    delete msgLabel;
    delete movie;
    delete movieLable;
}

void BusyWaitDialog::setMessage(const QString &msg)
{
    this->msgLabel->setText(msg);
}

void BusyWaitDialog::initUI()
{
    this->setWindowModality(Qt::NonModal);
    this->resize(437, 211);
    this->setWindowOpacity(1);
    this->movieLable = new QLabel();
    this->movieLable->setGeometry(QRect(200,20,100,100));
    this->msgLabel = new QLabel();
    this->msgLabel->setGeometry(QRect(10,160,417,41));
    QFont font;
    font.setFamily(QString::fromUtf8("Agency FB"));
    font.setPixelSize(18);
    font.setBold(true);
    font.setWeight(75);
    msgLabel->setFont(font);
    msgLabel->setAlignment(Qt::AlignCenter);
}
