#include "pluginsitem.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>

#include "contentmodule.h"

using namespace dtb;

PluginsItem::PluginsItem(PluginsItemInterface * const pluginInter, const QString &itemKey, QWidget *parent)
    : Item(parent)
    , m_pluginInter(pluginInter)
    , m_centralWidget(pluginInter->itemWidget(itemKey))
    , m_itemKey(itemKey)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_centralWidget, 0, Qt::AlignCenter);
    setLayout(mainLayout);
}

PluginsItem::~PluginsItem()
{
}

const QString PluginsItem::name() const
{
    return m_pluginInter->pluginName();
}

PluginsItemInterface *PluginsItem::itemInter()
{
    return m_pluginInter;
}

void PluginsItem::mouseReleaseEvent(QMouseEvent *event)
{
    Item::mouseReleaseEvent(event);

    showTips();
}

QMenu *PluginsItem::contextMenu() const
{
    return m_pluginInter->itemContextMenu(m_itemKey);
}

void PluginsItem::detachPluginWidget()
{
    QWidget *widget = m_pluginInter->itemWidget(m_itemKey);
    if (widget)
        widget->setParent(nullptr);
}

void PluginsItem::showTips()
{
    QPoint p(mapToGlobal(QPoint(pos().x(), height()) - pos()));
    if (itemInter()->itemPopupWindow(m_itemKey)) {
         if (PopupWindow->getContent()) {
             PopupWindow->getContent()->setParent(nullptr);
             PopupWindow->getContent()->hide();
         }

         PopupWindow->setContent(itemInter()->itemPopupWindow(m_itemKey));
         PopupWindow->show(p.x(), p.y());
         return;
    }

    QMenu* menu = contextMenu();
    if (!menu) {
        return;
    }

    menu->move(p);
    menu->exec();
}
