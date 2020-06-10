


#pragma once

#include <QPointF>


#include <vector>
#include <memory>


namespace App
{
    class fractal_generator;
    class line;

    class fractal_pattern_generator
    {
    public:
        explicit fractal_pattern_generator(const std::shared_ptr<fractal_generator>&);
        void generate_pattern();
        void push_point(QPointF);
        void surface_changed(uint32_t surface_width, uint32_t surface_height);
        std::unique_ptr<line> get_last_line() const;
        bool can_gen_pattern() const;
        void clear();

    private:
        std::vector<QPointF> m_points;
        std::shared_ptr<fractal_generator> m_fractals_generator;
        uint32_t m_surface_width, m_surface_height;
    };
}

