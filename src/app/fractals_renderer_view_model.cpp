

#include "fractals_renderer_view_model.hpp"

#include <src/app/fractal_generator.hpp>
#include <src/app/line.hpp>


App::fractals_renderer_view_model::fractals_renderer_view_model(
    QObject *parent,
    const std::shared_ptr<fractal_generator>& mdl)
    : QObject(parent)
    , m_model(mdl)
{
    m_model->subscribe_lines_handler([this]() {
        m_model->handle_lines([this](const std::vector<fractal_line>& fractal_lines) {
            m_lines.clear();

            if (!fractal_lines.empty()) {
                m_lines.reserve(fractal_lines.size() * fractal_lines.front().get_lines().size());

                for (const auto& fl : fractal_lines) {
                    for (const auto& l : fl.get_lines()) {
                        m_lines.emplace_back(line::create(l->get_begin(), l->get_end()));
                    }
                }

                emit initDraw();
            }
        });
    });
}


App::fractals_renderer_view_model::~fractals_renderer_view_model() = default;



QList<QObject*> App::fractals_renderer_view_model::get_lines() const
{
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
