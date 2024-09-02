#include "keyeventfilter.h"

KeyEventFilter::KeyEventFilter(QObject *parent)
    : QObject(parent)
{
}

bool KeyEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->modifiers() & Qt::ControlModifier) {
            switch (keyEvent->key()) {
            case Qt::Key_C:
                emit copyTriggered();
                qDebug() << "Ctrl+C Pressed";
                return true;
            case Qt::Key_V:
                emit pasteTriggered();
                return true;
            case Qt::Key_Z:
                emit undoTriggered();
                return true;
            case Qt::Key_Y:
                emit redoTriggered();
                return true;
            case Qt::Key_F:
                emit findTriggered();
                return true;
            default:
                break;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
