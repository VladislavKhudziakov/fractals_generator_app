

#include "fractals_renderer_view_model.hpp"

#include <src/app/fractal_generator.hpp>
#include <src/app/line.hpp>


App::fractals_renderer_view_model::fractals_renderer_view_model(
    QObject *parent,
    const std::shared_ptr<fractal_generator>& mdl)
    : QObject(parent)
    , m_model(mdl)
{
}


App::fractals_renderer_view_model::~fractals_renderer_view_model() = default;



QList<QObject*> App::fractals_renderer_view_model::get_lines() const
{
    m_lines.clear();

    m_lines = m_model->get_lines();

    QList<QObject*> res;

    for (const auto& l : m_lines) {
        res.push_back(l.get());
    }

    return res;
}


void App::fractals_renderer_view_model::mouse_clicked(qreal x, qreal y)
{
    m_model->push_point({x, y});
}


void App::fractals_renderer_view_model::calculate_fractal(qint64 gens)
{
    m_model->make_fractal(gens);
}


void App::fractals_renderer_view_model::on_surface_size_changed(qint64 width, qint64 height)
{

}
