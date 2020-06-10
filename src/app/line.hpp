


#pragma once

#include <QObject>
#include <QPointF>

namespace App
{
    class line : public QObject
    {
        Q_OBJECT
    public:
        Q_PROPERTY(QPointF begin READ get_begin)
        Q_PROPERTY(QPointF end READ get_end)

        line(QPointF, QPointF);
        static std::unique_ptr<line> create(QPointF, QPointF);

        QPointF get_begin() const;
        QPointF get_end() const;

    private:
        QPointF m_begin;
        QPointF m_end;
    };
}

