#pragma once
// 使用改宏生成之后需要手动加signals部分，结构如下
// signals:                                                                              \
//     type name##Changed(const type &##name);
#define X_Q_PROPERTY(type, name, up_name)                                             \
    Q_PROPERTY(type name READ get##up_name WRITE set####up_name NOTIFY name##Changed) \
private:                                                                              \
    type m_##name;                                                                    \
                                                                                      \
public:                                                                               \
    void set####up_name(const type &##name)                                           \
    {                                                                                 \
        if (name != this->m_##name)                                                   \
        {                                                                             \
            this->m_##name = name;                                                    \
            emit this->name##Changed(this->m_##name);                                 \
        }                                                                             \
    };                                                                                \
    type get##up_name()                                                               \
    {                                                                                 \
        return this->m_##name;                                                        \
    };

#include <QObject>
class Context : public QObject
{
    Q_OBJECT
    X_Q_PROPERTY(QString, text, Text)
public:
    explicit Context(QObject *parent = nullptr);
    ~Context();
signals:
    QString textChanged(const QString &text);
};