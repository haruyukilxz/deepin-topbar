#include "mediacontrol.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

namespace Plugin {
namespace MediaControl {
MediaControl::MediaControl(QWidget *parent) : QFrame(parent) {
    setWindowFlags(Qt::FramelessWindowHint);

    m_lastBtn = new FontLabel;
    m_lastBtn->setIcon(QChar(0xE76C), 18);
    m_lastBtn->installEventFilter(this);

    m_previousBtn = new FontLabel;
    m_previousBtn->setIcon(QChar(0xE76B), 18);
    m_previousBtn->installEventFilter(this);

    m_pauseBtn = new FontLabel;
    m_pauseBtn->installEventFilter(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);

    layout->addWidget(m_previousBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(m_pauseBtn, 0, Qt::AlignCenter | Qt::AlignVCenter);
    layout->addWidget(m_lastBtn, 0, Qt::AlignRight | Qt::AlignVCenter);

    setLayout(layout);
}

void MediaControl::setPlayState(MediaControl::PlayState state) {
    m_playState = state;

    switch (state) {
    case Play: {
        m_pauseBtn->setIcon(QChar(0xE769), 18);
        break;
    }
    case Stop:
        break;
    case Pause: {
        m_pauseBtn->setIcon(QChar(0xE768), 18);
        break;
    }
    case Last:
        break;
    case Previous:
        break;
    default:
        break;
    }
}

bool MediaControl::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_lastBtn) {
        if (event->type() == QMouseEvent::Enter)
            m_lastBtn->setStyleSheet("color: #00BFFF");
        if (event->type() == QMouseEvent::Leave)
            m_lastBtn->setStyleSheet("color: black");
        if (event->type() == QMouseEvent::MouseButtonPress)
            m_lastBtn->setStyleSheet("color: #1E90FF");
        if (event->type() == QMouseEvent::MouseButtonRelease)
            emit requestLast();
    }

    if (watched == m_previousBtn) {
        if (event->type() == QMouseEvent::Enter)
            m_previousBtn->setStyleSheet("color: #00BFFF");
        if (event->type() == QMouseEvent::Leave)
            m_previousBtn->setStyleSheet("color: black");
        if (event->type() == QMouseEvent::MouseButtonPress)
            m_previousBtn->setStyleSheet("color: #1E90FF");
        if (event->type() == QMouseEvent::MouseButtonRelease)
            emit requestPrevious();
    }

    if (watched == m_pauseBtn) {
        if (event->type() == QMouseEvent::Enter)
            m_pauseBtn->setStyleSheet("color: #00BFFF");
        if (event->type() == QMouseEvent::Leave)
            m_pauseBtn->setStyleSheet("color: black");
        if (event->type() == QMouseEvent::MouseButtonPress)
            m_pauseBtn->setStyleSheet("color: #1E90FF");
        if (event->type() == QMouseEvent::MouseButtonRelease)
            emit requestPause();
    }

    return false;
}

}
}
