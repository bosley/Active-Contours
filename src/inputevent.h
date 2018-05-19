#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

class InputEventVD : public QObject
{
    Q_OBJECT

public:
    InputEventVD(){}
    ~InputEventVD(){}

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

bool InputEventVD::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);


        qDebug() << "Ate key press " << keyEvent->key() ;

        return true;

    } else if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);

        qDebug() << mEvent->x() << ", " << mEvent->y();

        return true;

    } else {

        return QObject::eventFilter(obj, event);
    }
}

#endif // INPUTEVENT_H
