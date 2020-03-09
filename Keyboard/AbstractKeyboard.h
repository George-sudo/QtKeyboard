﻿/**********************************************************
Author: Qt君
微信公众号: Qt君(首发)
QQ群: 732271126
Email: 2088201923@qq.com
LICENSE: MIT
**********************************************************/

#ifndef AEA_ABSTRACT_KEYBOARD_H
#define AEA_ABSTRACT_KEYBOARD_H

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QKeyEvent>

namespace AeaQt {

class AbstractKeyboard : public QWidget
{
    Q_OBJECT
public:
    AbstractKeyboard(QWidget *parent = nullptr) : QWidget(parent) {

    }
    ~AbstractKeyboard() { }

    const QString name() { return m_name; }
    void setName(const QString &name) { m_name = name; }

public slots:
    virtual void update(const QString &text) { Q_UNUSED(text); }

    void onKeyPressed(int key, QString value)
    {
        qDebug() << "key: " << key << "Value: " << value;
        QWidget *receiver = QApplication::focusWidget();
        if (!receiver)
            return;

        QKeyEvent keyPress(QEvent::KeyPress,     key, Qt::NoModifier, value);
        QKeyEvent keyRelease(QEvent::KeyRelease, key, Qt::NoModifier, value);

        QApplication::sendEvent(receiver, &keyPress);
        QApplication::sendEvent(receiver, &keyRelease);
    }

signals:
    void keyPressed(int key, QString value);

private:
    QString m_name;
};

}
#endif // AEA_ABSTRACT_KEYBOARD_H
