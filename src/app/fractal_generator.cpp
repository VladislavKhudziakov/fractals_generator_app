

#include "fractal_generator.hpp"

#include <src/app/line.hpp>

#include <QTransform>
#include <QVector3D>
#include <QMatrix3x3>

#include <thread>


App::fractal_line::fractal_line(QPointF begin, QPointF end)
{
    const auto x = end - begin;
    const QPointF y {x.y(), -x.x()};

    m_transformation.setMatrix(x.x(), y.x(), 0, x.y(), y.y(), 0, begin.x(), begin.y(), 1.f);
}


const std::vector<std::unique_ptr<App::line>>& App::fractal_line::get_lines() const
{
    return m_lines;
}


void App::fractal_line::generate(const std::vector<QPointF>& points)
{
    std::vector<QPointF> transformated_points;
    transformated_points.reserve(points.size());
    std::transform(points.begin(), points.end(), std::back_inserter(transformated_points), [this](const QPointF& p) {
        return m_transformation.map(p);
    });

    for (int i = 1; i < transformated_points.size(); ++i) {
        m_lines.emplace_back(line::create(transformated_points[i - 1], transformated_points[i]));
    }
}


void App::fractal_generator::make_fractal(uint32_t depth)
{
    std::thread t([this, depth]() {
        std::lock_guard lines_guard(m_lines_mutex);
        m_lines.clear();

        std::unique_lock points_guard(m_points_mutex);

        if (m_points.size() % 2 != 0) {
            return;
        }

        while (!m_points.empty()) {
            const auto e = m_points.top();
            m_points.pop();
            const auto b = m_points.top();
            m_points.pop();
            auto& line = m_lines.emplace_back(b, e);
            line.generate(m_points_pattern);
        }

        points_guard.unlock();

        std::lock_guard pattern_guard(m_points_pattern_mutex);

        for (size_t i = 0; i < depth; ++i) {
            make_fractals_generation();
        }

          std::lock_guard g(m_lines_handlers_mutex);

        for (const auto& handler : m_lines_handlers) {
            handler();
        }
    });

    t.detach();
}


void App::fractal_generator::make_fractals_generation()
{
    std::vector<fractal_line> new_lines;

    if (m_lines.empty()) {
        return;
    }

    new_lines.reserve(m_lines.size() * m_lines.front().get_lines().size());

    for (const auto& fl : m_lines) {
        for (const auto& l : fl.get_lines()) {
            auto& new_line = new_lines.emplace_back(l->get_begin(), l->get_end());
            new_line.generate(m_points_pattern);
        }
    }

     m_lines = std::move(new_lines);
}


void App::fractal_generator::push_point(QPointF p)
{
    std::lock_guard g(m_points_pattern_mutex);
    m_points.push(p);
}


void App::fractal_generator::set_points_pattern(const std::vector<QPointF>& new_pattern)
{
    std::lock_guard g(m_points_pattern_mutex);
    m_points_pattern = new_pattern;
}


App::fractal_generator::fractal_generator()
{
    QPointF b1 {0, 0};
    QPointF e1 {1, 0};

    auto v3 = (e1 - b1) / 3;

    auto a = b1;
    auto b = a + v3;

    QTransform t;
    t.rotate(60);

    auto c = b + t.map(v3);
    auto d = b + v3;
    auto e = d + v3;

    m_points_pattern = {
        a, b, c, d, e
    };
}


void App::fractal_generator::subscribe_lines_handler(const App::fractal_generator::lines_handler& h)
{
    std::lock_guard g(m_lines_handlers_mutex);
    m_lines_handlers.emplace_back(h);
}
