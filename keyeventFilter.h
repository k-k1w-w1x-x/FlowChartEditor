#ifndef KEYEVENTFILTER_H
#define KEYEVENTFILTER_H

#include <QObject>
#include <QKeyEvent>

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

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // KEYEVENTFILTER_H
