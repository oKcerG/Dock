#include "dock.h"
#include <QQmlInfo>

Dock::Dock(QQuickItem *item) : QObject(item),
    m_anchors{item->property("anchors").value<QObject*>()}
{
}

void Dock::applyAnchorLines(QQuickItem *otherItem, const QVector<QString> &anchorLines)
{
    for (const QString& anchorLine : anchorLines)
        QQmlProperty::write(m_anchors, anchorLine, QQmlProperty::read(otherItem, anchorLine));
}

void Dock::resetAnchorLines(const QVector<QString> &anchorLines)
{
    for (const QString& anchorLine : anchorLines)
        QQmlProperty(m_anchors, anchorLine).reset();
}

Dock* Dock::qmlAttachedProperties(QObject *object)
{
    QQuickItem *item = qobject_cast<QQuickItem *>(object);
    if (!item) {
        qmlInfo(object) << "Dock must be attached to an Item";
        return nullptr;
    }
    return new Dock(item);
}

struct DockTypeRegisterHelper {
    DockTypeRegisterHelper()
    {
        qmlRegisterUncreatableType<Dock>("Dock", 0, 1, "Dock", "Dock is only available via attached properties");
    }
};

static const DockTypeRegisterHelper typeRegisterHelper;
