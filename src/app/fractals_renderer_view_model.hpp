


#pragma once

#include <QObject>
#include <QPointF>

#include <memory>
#include <stack>



namespace App
{
    class fractal_generator;
    class line;

    class fractals_renderer_view_model : public QObject
    {
        Q_OBJECT
    public:
        Q_PROPERTY(QList<QObject*> lines READ get_lines);

        fractals_renderer_view_model(QObject* parent, const std::shared_ptr<fractal_generator>& mdl);
        ~fractals_renderer_view_model() override;
        QList<QObject*> get_lines() const;

        Q_INVOKABLE void mouse_clicked(qreal x, qreal y);
        Q_INVOKABLE void calculate_fractal(qint64 gens);

    signals:
        void initDraw();

    public slots:
            void on_surface_size_changed(qint64 width, qint64 height);
    private:
        std::shared_ptr<fractal_generator> m_model;
        mutable std::vector<std::unique_ptr<line>> m_lines;
    };
}

