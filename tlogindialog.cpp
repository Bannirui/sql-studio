#include<QMouseEvent>
#include<QPoint>

#include "tlogindialog.h"
#include "ui_tlogindialog.h"

TLoginDialog::TLoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TLoginDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::SplashScreen);
}

TLoginDialog::~TLoginDialog()
{
    delete ui;
}

void TLoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    this->m_moving=false;
    event->accept();
}

void TLoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    QPoint eventPos=event->globalPosition().toPoint();
    if(this->m_moving && (event->button()&Qt::LeftButton) && (eventPos-m_lastPos-this->pos()).manhattanLength()>QApplication::startDragDistance())
    {
        move(eventPos-this->m_lastPos);
        this->m_lastPos=eventPos-this->pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void TLoginDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        this->m_moving=true;
        this->m_lastPos=event->globalPosition().toPoint()-this->pos();
    }
    return QDialog::mousePressEvent(event);
}

