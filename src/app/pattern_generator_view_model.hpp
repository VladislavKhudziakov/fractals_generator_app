


#pragma once

#include <QObject>

#include <memory>

namespace App
{
    class fractal_pattern_generator;
    class line;


    class pattern_generator_view_model : public QObject
    {
        Q_OBJECT
    public:
        Q_PROPERTY(QList<QObject*> lines READ get_last_line);
        pattern_generator_view_model(QObject* parent, const std::shared_ptr<fractal_pattern_generator>& g);

        Q_INVOKABLE void mouse_clicked(qreal x, qreal y);
        QList<QObject*> get_last_line() const;

        Q_INVOKABLE bool can_generate_pattern();
        Q_INVOKABLE void clear();
        Q_INVOKABLE void apply_pattern();

    signals:
        void initDraw();

    public slots:
        void on_surface_size_changed(qint64 width, qint64 height);

    private:
        std::shared_ptr<fractal_pattern_generator> m_pattern_generator;
        mutable std::unique_ptr<line> m_last_line;
    };
}
