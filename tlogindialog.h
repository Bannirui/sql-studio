#ifndef TLOGINDIALOG_H
#define TLOGINDIALOG_H

#include <QDialog>

namespace Ui {
class TLoginDialog;
}

class TLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TLoginDialog(QWidget *parent = nullptr);
    ~TLoginDialog();

private:
    Ui::TLoginDialog *ui;
    bool m_moving;
    QPoint m_lastPos;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // TLOGINDIALOG_H
