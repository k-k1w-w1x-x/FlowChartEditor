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
                break;
            case Qt::Key_V:
                emit pasteTriggered();
                break;
            case Qt::Key_Z:
                emit undoTriggered();
                break;
            case Qt::Key_Y:
                emit redoTriggered();
                break;
            case Qt::Key_X:
                emit cutTriggered();
                break;
            case Qt::Key_F:
                emit findTriggered();
                break;
            case Qt::Key_Backspace:
                emit deleteTriggered();
            default:
                break;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
