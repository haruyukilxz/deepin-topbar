#include "networkpopupwidget.h"
#include <QVBoxLayout>

NetworkPopupWidget::NetworkPopupWidget(QWidget *parent) : QWidget(parent)
{
    resize(300, 100);

    QVBoxLayout *layout = new QVBoxLayout;

    setLayout(layout);

    m_showAni = new QPropertyAnimation(this, "size", this);
    m_showAni->setDuration(300);
    m_showAni->setStartValue(QSize(width(), 30));
    m_showAni->setEndValue(size());
    m_showAni->setEasingCurve(QEasingCurve::InOutCubic);

    m_hideAni = new QPropertyAnimation(this, "size", this);
    m_hideAni->setDuration(300);
    m_hideAni->setStartValue(size());
    m_hideAni->setEndValue(QSize(width(), 30));
    m_hideAni->setEasingCurve(QEasingCurve::InOutCubic);

    connect(m_hideAni, &QPropertyAnimation::finished, this, &NetworkPopupWidget::requestHidePopup);


    //load Network
}

void NetworkPopupWidget::showAni()
{
    m_showAni->start();
}

void NetworkPopupWidget::hideAni()
{
    m_hideAni->start();
}
