

#include "pattern_generator_view_model.hpp"

#include <src/app/fractal_pattern_generator.hpp>
#include <src/app/line.hpp>

#include <QDebug>

App::pattern_generator_view_model::pattern_generator_view_model(
    QObject *parent, const std::shared_ptr<fractal_pattern_generator>& g)
    : QObject(parent)
    , m_pattern_generator(g)
{
}


void App::pattern_generator_view_model::mouse_clicked(qreal x, qreal y)
{
    m_pattern_generator->push_point({x, y});
    emit initDraw();
}


QList<QObject *> App::pattern_generator_view_model::get_last_line() const
{
    QList<QObject*> ret;

    m_last_line = m_pattern_generator->get_last_line();

    if (m_last_line != nullptr) {
        ret.push_back(m_last_line.get());
    }

    return ret;
}


void App::pattern_generator_view_model::on_surface_size_changed(qint64 width, qint64 height)
{
    m_pattern_generator->surface_changed(width, height);
}


bool App::pattern_generator_view_model::can_generate_pattern()
{
    return m_pattern_generator->can_gen_pattern();
}


void App::pattern_generator_view_model::clear()
{
    m_pattern_generator->clear();
}


void App::pattern_generator_view_model::apply_pattern()
{
    m_pattern_generator->generate_pattern();
}
