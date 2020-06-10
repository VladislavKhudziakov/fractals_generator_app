

#include "fractal_pattern_generator.hpp"

#include <src/app/fractal_generator.hpp>
#include <src/app/line.hpp>


App::fractal_pattern_generator::fractal_pattern_generator(const std::shared_ptr<fractal_generator>& fg)
    : m_fractals_generator(fg)
{
}


void App::fractal_pattern_generator::generate_pattern()
{
    std::transform(m_points.begin(), m_points.end(), m_points.begin(), [this](QPointF p) {
        return QPointF{p.x() / m_surface_width, (m_surface_height / 2.f - p.y()) / (m_surface_height / 2.f)};
    });

    m_points.insert(m_points.begin(), QPointF{0, 0});
    m_points.emplace_back(QPointF{1, 0});

    m_fractals_generator->set_points_pattern(m_points);

    m_points.clear();
}


void App::fractal_pattern_generator::push_point(QPointF p)
{
    m_points.emplace_back(p);
}


void App::fractal_pattern_generator::surface_changed(uint32_t surface_width, uint32_t surface_height)
{
    m_surface_width = surface_width;
    m_surface_height = surface_height;
}


std::unique_ptr<App::line> App::fractal_pattern_generator::get_last_line() const
{
    if (m_points.size() > 1) {
        return line::create(*(m_points.rbegin() + 1), *m_points.rbegin());
    }

    return nullptr;
}


bool App::fractal_pattern_generator::can_gen_pattern() const
{
    return m_points.size() >= 3;
}


void App::fractal_pattern_generator::clear()
{
    m_points.clear();
}
