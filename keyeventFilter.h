#ifndef KEYEVENTFILTER_H
#define KEYEVENTFILTER_H

#include <QObject>
#include <QKeyEvent>
#include <flowelement.h>

class KeyEventFilter : public QObject
{
    Q_OBJECT

public:
    explicit KeyEventFilter(QObject *parent = nullptr);

signals:
    void copyTriggered();
    void pasteTriggered();
    void undoTriggered();
    void redoTriggered();
    void findTriggered();
    void deleteTriggered();
    void cutTriggered();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // KEYEVENTFILTER_H
