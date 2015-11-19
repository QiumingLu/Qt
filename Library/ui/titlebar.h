#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

class QToolButton;
class QLabel;
class QHBoxLayout;
class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();
    void setWindowIcon(const QIcon &pix);
    void setTitleTransparent();

signals:
    void minimized();
    void closed();
    void maxRestored();
    void moved(const QPoint &delta);

public slots:
    void showMaxRestore(const bool maximized);
    void setWindowTitle(const QString &title);
    void setWindowModified(bool mod);
    void setMinimizeVisible(bool visible);
    void setMaximizeVisible(bool visible);
    void setCloseVisible(bool visible);

protected:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
    void mouseDoubleClickEvent(QMoveEvent *);


private:
    bool maxNormal;
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QLabel *label;
    QLabel *icon;
    QHBoxLayout *hbox;
    QPixmap restorePix, maxPix;
    QPoint startPos;
    QPoint clickPos;

};

#endif // TITLEBAR_H
