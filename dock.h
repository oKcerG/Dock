#ifndef DOCK_H
#define DOCK_H

#include <QObject>
#include <QQuickItem>
#include <QtQml>

#define DOCK_PROPERTY(name, ... ) \
        Q_PROPERTY (QQuickItem* name READ name WRITE set_##name RESET reset_##name NOTIFY name##Changed) \
    public: \
        QQuickItem * name() const\
        { \
            return m_##name ; \
        } \
    void set_##name(QQuickItem* name)\
    { \
        if (m_##name != name)\
        { \
            m_##name = name; \
            applyAnchorLines(name, { __VA_ARGS__ });\
            emit name##Changed(); \
        } \
    } \
    void reset_##name()\
    { \
        if (m_##name != nullptr)\
        { \
            m_##name = nullptr; \
            resetAnchorLines({ __VA_ARGS__ });\
            emit name##Changed(); \
        } \
    } \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        QQuickItem * m_##name = nullptr;

class Dock : public QObject
{
    Q_OBJECT
    DOCK_PROPERTY(top, "top", "left", "right")
    DOCK_PROPERTY(bottom, "bottom", "left", "right")
    DOCK_PROPERTY(left, "left", "top", "bottom")
    DOCK_PROPERTY(right, "right", "top", "bottom")
    DOCK_PROPERTY(vertically, "top", "bottom")
    DOCK_PROPERTY(horizontally, "left", "right")
    DOCK_PROPERTY(topLeft, "top", "left")
    DOCK_PROPERTY(topRight, "top", "right")
    DOCK_PROPERTY(bottomLeft, "bottom", "left")
    DOCK_PROPERTY(bottomRight, "bottom", "right")

public:
    explicit Dock(QQuickItem *item = nullptr);
    static Dock* qmlAttachedProperties(QObject *object);

private:
    void applyAnchorLines(QQuickItem* otherItem, const QVector<QString>& anchorLines);
    void resetAnchorLines(const QVector<QString>& anchorLines);
    QObject* m_anchors;
};
QML_DECLARE_TYPEINFO(Dock, QML_HAS_ATTACHED_PROPERTIES)

#endif // DOCK_H
